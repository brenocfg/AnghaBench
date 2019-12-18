#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct r820t_sect_type {int /*<<< orphan*/  value; int /*<<< orphan*/  phase_y; int /*<<< orphan*/  gain_x; } ;
struct r820t_priv {TYPE_2__* imr_data; int /*<<< orphan*/  has_lock; TYPE_1__* cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  phase_y; int /*<<< orphan*/  gain_x; } ;
struct TYPE_3__ {int xtal; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_TUNER_DIGITAL_TV ; 
 int r820t_f_imr (struct r820t_priv*,struct r820t_sect_type*) ; 
 int r820t_iq (struct r820t_priv*,struct r820t_sect_type*) ; 
 int r820t_read_cache_reg (struct r820t_priv*,int) ; 
 int r820t_set_mux (struct r820t_priv*,int) ; 
 int r820t_set_pll (struct r820t_priv*,int /*<<< orphan*/ ,int) ; 
 int r820t_write_reg (struct r820t_priv*,int,int) ; 

__attribute__((used)) static int r820t_imr(struct r820t_priv *priv, unsigned imr_mem, bool im_flag)
{
	struct r820t_sect_type imr_point;
	int rc;
	u32 ring_vco, ring_freq, ring_ref;
	u8 n_ring, n;
	int reg18, reg19, reg1f;

	if (priv->cfg->xtal > 24000000)
		ring_ref = priv->cfg->xtal / 2000;
	else
		ring_ref = priv->cfg->xtal / 1000;

	n_ring = 15;
	for (n = 0; n < 16; n++) {
		if ((16 + n) * 8 * ring_ref >= 3100000) {
			n_ring = n;
			break;
		}
	}

	reg18 = r820t_read_cache_reg(priv, 0x18);
	reg19 = r820t_read_cache_reg(priv, 0x19);
	reg1f = r820t_read_cache_reg(priv, 0x1f);

	reg18 &= 0xf0;      /* set ring[3:0] */
	reg18 |= n_ring;

	ring_vco = (16 + n_ring) * 8 * ring_ref;

	reg18 &= 0xdf;   /* clear ring_se23 */
	reg19 &= 0xfc;   /* clear ring_seldiv */
	reg1f &= 0xfc;   /* clear ring_att */

	switch (imr_mem) {
	case 0:
		ring_freq = ring_vco / 48;
		reg18 |= 0x20;  /* ring_se23 = 1 */
		reg19 |= 0x03;  /* ring_seldiv = 3 */
		reg1f |= 0x02;  /* ring_att 10 */
		break;
	case 1:
		ring_freq = ring_vco / 16;
		reg18 |= 0x00;  /* ring_se23 = 0 */
		reg19 |= 0x02;  /* ring_seldiv = 2 */
		reg1f |= 0x00;  /* pw_ring 00 */
		break;
	case 2:
		ring_freq = ring_vco / 8;
		reg18 |= 0x00;  /* ring_se23 = 0 */
		reg19 |= 0x01;  /* ring_seldiv = 1 */
		reg1f |= 0x03;  /* pw_ring 11 */
		break;
	case 3:
		ring_freq = ring_vco / 6;
		reg18 |= 0x20;  /* ring_se23 = 1 */
		reg19 |= 0x00;  /* ring_seldiv = 0 */
		reg1f |= 0x03;  /* pw_ring 11 */
		break;
	case 4:
		ring_freq = ring_vco / 4;
		reg18 |= 0x00;  /* ring_se23 = 0 */
		reg19 |= 0x00;  /* ring_seldiv = 0 */
		reg1f |= 0x01;  /* pw_ring 01 */
		break;
	default:
		ring_freq = ring_vco / 4;
		reg18 |= 0x00;  /* ring_se23 = 0 */
		reg19 |= 0x00;  /* ring_seldiv = 0 */
		reg1f |= 0x01;  /* pw_ring 01 */
		break;
	}


	/* write pw_ring, n_ring, ringdiv2 registers */

	/* n_ring, ring_se23 */
	rc = r820t_write_reg(priv, 0x18, reg18);
	if (rc < 0)
		return rc;

	/* ring_sediv */
	rc = r820t_write_reg(priv, 0x19, reg19);
	if (rc < 0)
		return rc;

	/* pw_ring */
	rc = r820t_write_reg(priv, 0x1f, reg1f);
	if (rc < 0)
		return rc;

	/* mux input freq ~ rf_in freq */
	rc = r820t_set_mux(priv, (ring_freq - 5300) * 1000);
	if (rc < 0)
		return rc;

	rc = r820t_set_pll(priv, V4L2_TUNER_DIGITAL_TV,
			   (ring_freq - 5300) * 1000);
	if (!priv->has_lock)
		rc = -EINVAL;
	if (rc < 0)
		return rc;

	if (im_flag) {
		rc = r820t_iq(priv, &imr_point);
	} else {
		imr_point.gain_x  = priv->imr_data[3].gain_x;
		imr_point.phase_y = priv->imr_data[3].phase_y;
		imr_point.value   = priv->imr_data[3].value;

		rc = r820t_f_imr(priv, &imr_point);
	}
	if (rc < 0)
		return rc;

	/* save IMR value */
	switch (imr_mem) {
	case 0:
		priv->imr_data[0].gain_x  = imr_point.gain_x;
		priv->imr_data[0].phase_y = imr_point.phase_y;
		priv->imr_data[0].value   = imr_point.value;
		break;
	case 1:
		priv->imr_data[1].gain_x  = imr_point.gain_x;
		priv->imr_data[1].phase_y = imr_point.phase_y;
		priv->imr_data[1].value   = imr_point.value;
		break;
	case 2:
		priv->imr_data[2].gain_x  = imr_point.gain_x;
		priv->imr_data[2].phase_y = imr_point.phase_y;
		priv->imr_data[2].value   = imr_point.value;
		break;
	case 3:
		priv->imr_data[3].gain_x  = imr_point.gain_x;
		priv->imr_data[3].phase_y = imr_point.phase_y;
		priv->imr_data[3].value   = imr_point.value;
		break;
	case 4:
		priv->imr_data[4].gain_x  = imr_point.gain_x;
		priv->imr_data[4].phase_y = imr_point.phase_y;
		priv->imr_data[4].value   = imr_point.value;
		break;
	default:
		priv->imr_data[4].gain_x  = imr_point.gain_x;
		priv->imr_data[4].phase_y = imr_point.phase_y;
		priv->imr_data[4].value   = imr_point.value;
		break;
	}

	return 0;
}