#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct r820t_priv {int xtal_cap_sel; TYPE_1__* imr_data; scalar_t__ imr_done; } ;
struct r820t_freq_range {int freq; int open_d; int rf_mux_ploy; int xtal_cap20p; int xtal_cap10p; int xtal_cap0p; size_t imr_mem; int /*<<< orphan*/  tf_c; } ;
struct TYPE_2__ {int gain_x; int phase_y; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct r820t_freq_range*) ; 
#define  XTAL_HIGH_CAP_0P 132 
#define  XTAL_LOW_CAP_0P 131 
#define  XTAL_LOW_CAP_10P 130 
#define  XTAL_LOW_CAP_20P 129 
#define  XTAL_LOW_CAP_30P 128 
 struct r820t_freq_range* freq_ranges ; 
 int r820t_write_reg (struct r820t_priv*,int,int /*<<< orphan*/ ) ; 
 int r820t_write_reg_mask (struct r820t_priv*,int,int,int) ; 
 int /*<<< orphan*/  tuner_dbg (char*,int,int) ; 

__attribute__((used)) static int r820t_set_mux(struct r820t_priv *priv, u32 freq)
{
	const struct r820t_freq_range *range;
	int i, rc;
	u8 val, reg08, reg09;

	/* Get the proper frequency range */
	freq = freq / 1000000;
	for (i = 0; i < ARRAY_SIZE(freq_ranges) - 1; i++) {
		if (freq < freq_ranges[i + 1].freq)
			break;
	}
	range = &freq_ranges[i];

	tuner_dbg("set r820t range#%d for frequency %d MHz\n", i, freq);

	/* Open Drain */
	rc = r820t_write_reg_mask(priv, 0x17, range->open_d, 0x08);
	if (rc < 0)
		return rc;

	/* RF_MUX,Polymux */
	rc = r820t_write_reg_mask(priv, 0x1a, range->rf_mux_ploy, 0xc3);
	if (rc < 0)
		return rc;

	/* TF BAND */
	rc = r820t_write_reg(priv, 0x1b, range->tf_c);
	if (rc < 0)
		return rc;

	/* XTAL CAP & Drive */
	switch (priv->xtal_cap_sel) {
	case XTAL_LOW_CAP_30P:
	case XTAL_LOW_CAP_20P:
		val = range->xtal_cap20p | 0x08;
		break;
	case XTAL_LOW_CAP_10P:
		val = range->xtal_cap10p | 0x08;
		break;
	case XTAL_HIGH_CAP_0P:
		val = range->xtal_cap0p | 0x00;
		break;
	default:
	case XTAL_LOW_CAP_0P:
		val = range->xtal_cap0p | 0x08;
		break;
	}
	rc = r820t_write_reg_mask(priv, 0x10, val, 0x0b);
	if (rc < 0)
		return rc;

	if (priv->imr_done) {
		reg08 = priv->imr_data[range->imr_mem].gain_x;
		reg09 = priv->imr_data[range->imr_mem].phase_y;
	} else {
		reg08 = 0;
		reg09 = 0;
	}
	rc = r820t_write_reg_mask(priv, 0x08, reg08, 0x3f);
	if (rc < 0)
		return rc;

	rc = r820t_write_reg_mask(priv, 0x09, reg09, 0x3f);

	return rc;
}