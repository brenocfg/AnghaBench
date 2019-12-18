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
typedef  int u16 ;
struct r820t_priv {int has_lock; TYPE_1__* cfg; } ;
typedef  enum v4l2_tuner_type { ____Placeholder_v4l2_tuner_type } v4l2_tuner_type ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_2__ {int xtal; scalar_t__ rafael_chip; } ;

/* Variables and functions */
 scalar_t__ CHIP_R620D ; 
 scalar_t__ CHIP_R828 ; 
 scalar_t__ CHIP_R828D ; 
 int V4L2_TUNER_DIGITAL_TV ; 
 int VCO_POWER_REF ; 
 int r820t_read (struct r820t_priv*,int,int*,int) ; 
 int r820t_write_reg (struct r820t_priv*,int,int) ; 
 int r820t_write_reg_mask (struct r820t_priv*,int,int,int) ; 
 int /*<<< orphan*/  tuner_dbg (char*,int,...) ; 
 int /*<<< orphan*/  usleep_range (unsigned int,unsigned int) ; 

__attribute__((used)) static int r820t_set_pll(struct r820t_priv *priv, enum v4l2_tuner_type type,
			 u32 freq)
{
	u32 vco_freq;
	int rc, i;
	unsigned sleep_time = 10000;
	u32 vco_fra;		/* VCO contribution by SDM (kHz) */
	u32 vco_min  = 1770000;
	u32 vco_max  = vco_min * 2;
	u32 pll_ref;
	u16 n_sdm = 2;
	u16 sdm = 0;
	u8 mix_div = 2;
	u8 div_buf = 0;
	u8 div_num = 0;
	u8 refdiv2 = 0;
	u8 ni, si, nint, vco_fine_tune, val;
	u8 data[5];

	/* Frequency in kHz */
	freq = freq / 1000;
	pll_ref = priv->cfg->xtal / 1000;

#if 0
	/* Doesn't exist on rtl-sdk, and on field tests, caused troubles */
	if ((priv->cfg->rafael_chip == CHIP_R620D) ||
	   (priv->cfg->rafael_chip == CHIP_R828D) ||
	   (priv->cfg->rafael_chip == CHIP_R828)) {
		/* ref set refdiv2, reffreq = Xtal/2 on ATV application */
		if (type != V4L2_TUNER_DIGITAL_TV) {
			pll_ref /= 2;
			refdiv2 = 0x10;
			sleep_time = 20000;
		}
	} else {
		if (priv->cfg->xtal > 24000000) {
			pll_ref /= 2;
			refdiv2 = 0x10;
		}
	}
#endif

	rc = r820t_write_reg_mask(priv, 0x10, refdiv2, 0x10);
	if (rc < 0)
		return rc;

	/* set pll autotune = 128kHz */
	rc = r820t_write_reg_mask(priv, 0x1a, 0x00, 0x0c);
	if (rc < 0)
		return rc;

	/* set VCO current = 100 */
	rc = r820t_write_reg_mask(priv, 0x12, 0x80, 0xe0);
	if (rc < 0)
		return rc;

	/* Calculate divider */
	while (mix_div <= 64) {
		if (((freq * mix_div) >= vco_min) &&
		   ((freq * mix_div) < vco_max)) {
			div_buf = mix_div;
			while (div_buf > 2) {
				div_buf = div_buf >> 1;
				div_num++;
			}
			break;
		}
		mix_div = mix_div << 1;
	}

	rc = r820t_read(priv, 0x00, data, sizeof(data));
	if (rc < 0)
		return rc;

	vco_fine_tune = (data[4] & 0x30) >> 4;

	tuner_dbg("mix_div=%d div_num=%d vco_fine_tune=%d\n",
			mix_div, div_num, vco_fine_tune);

	/*
	 * XXX: R828D/16MHz seems to have always vco_fine_tune=1.
	 * Due to that, this calculation goes wrong.
	 */
	if (priv->cfg->rafael_chip != CHIP_R828D) {
		if (vco_fine_tune > VCO_POWER_REF)
			div_num = div_num - 1;
		else if (vco_fine_tune < VCO_POWER_REF)
			div_num = div_num + 1;
	}

	rc = r820t_write_reg_mask(priv, 0x10, div_num << 5, 0xe0);
	if (rc < 0)
		return rc;

	vco_freq = freq * mix_div;
	nint = vco_freq / (2 * pll_ref);
	vco_fra = vco_freq - 2 * pll_ref * nint;

	/* boundary spur prevention */
	if (vco_fra < pll_ref / 64) {
		vco_fra = 0;
	} else if (vco_fra > pll_ref * 127 / 64) {
		vco_fra = 0;
		nint++;
	} else if ((vco_fra > pll_ref * 127 / 128) && (vco_fra < pll_ref)) {
		vco_fra = pll_ref * 127 / 128;
	} else if ((vco_fra > pll_ref) && (vco_fra < pll_ref * 129 / 128)) {
		vco_fra = pll_ref * 129 / 128;
	}

	ni = (nint - 13) / 4;
	si = nint - 4 * ni - 13;

	rc = r820t_write_reg(priv, 0x14, ni + (si << 6));
	if (rc < 0)
		return rc;

	/* pw_sdm */
	if (!vco_fra)
		val = 0x08;
	else
		val = 0x00;

	rc = r820t_write_reg_mask(priv, 0x12, val, 0x08);
	if (rc < 0)
		return rc;

	/* sdm calculator */
	while (vco_fra > 1) {
		if (vco_fra > (2 * pll_ref / n_sdm)) {
			sdm = sdm + 32768 / (n_sdm / 2);
			vco_fra = vco_fra - 2 * pll_ref / n_sdm;
			if (n_sdm >= 0x8000)
				break;
		}
		n_sdm = n_sdm << 1;
	}

	tuner_dbg("freq %d kHz, pll ref %d%s, sdm=0x%04x\n",
		  freq, pll_ref, refdiv2 ? " / 2" : "", sdm);

	rc = r820t_write_reg(priv, 0x16, sdm >> 8);
	if (rc < 0)
		return rc;
	rc = r820t_write_reg(priv, 0x15, sdm & 0xff);
	if (rc < 0)
		return rc;

	for (i = 0; i < 2; i++) {
		usleep_range(sleep_time, sleep_time + 1000);

		/* Check if PLL has locked */
		rc = r820t_read(priv, 0x00, data, 3);
		if (rc < 0)
			return rc;
		if (data[2] & 0x40)
			break;

		if (!i) {
			/* Didn't lock. Increase VCO current */
			rc = r820t_write_reg_mask(priv, 0x12, 0x60, 0xe0);
			if (rc < 0)
				return rc;
		}
	}

	if (!(data[2] & 0x40)) {
		priv->has_lock = false;
		return 0;
	}

	priv->has_lock = true;
	tuner_dbg("tuner has lock at frequency %d kHz\n", freq);

	/* set pll autotune = 8kHz */
	rc = r820t_write_reg_mask(priv, 0x1a, 0x08, 0x08);

	return rc;
}