#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct mga_device {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_DATA ; 
 int /*<<< orphan*/  DAC_INDEX ; 
 scalar_t__ G200_EW3 ; 
 int MGA1064_PIX_CLK_CTL ; 
 int MGA1064_PIX_CLK_CTL_CLK_DIS ; 
 int MGA1064_PIX_CLK_CTL_CLK_POW_DOWN ; 
 int MGA1064_PIX_CLK_CTL_SEL_MSK ; 
 int MGA1064_PIX_CLK_CTL_SEL_PLL ; 
 int MGA1064_REMHEADCTL ; 
 int MGA1064_REMHEADCTL_CLKDIS ; 
 int MGA1064_REMHEADCTL_CLKSL_MSK ; 
 int MGA1064_REMHEADCTL_CLKSL_PLL ; 
 int MGA1064_VREF_CTL ; 
 int MGA1064_WB_PIX_PLLC_M ; 
 int MGA1064_WB_PIX_PLLC_N ; 
 int MGA1064_WB_PIX_PLLC_P ; 
 int /*<<< orphan*/  MGAREG_CRTC_DATA ; 
 int /*<<< orphan*/  MGAREG_CRTC_INDEX ; 
 int /*<<< orphan*/  MGAREG_MEM_MISC_READ ; 
 int /*<<< orphan*/  MGAREG_MEM_MISC_WRITE ; 
 int /*<<< orphan*/  MGAREG_SEQ_DATA ; 
 int /*<<< orphan*/  MGAREG_SEQ_INDEX ; 
 int /*<<< orphan*/  MGAREG_VCOUNT ; 
 int RREG8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG_DAC (int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mga_g200wb_set_plls(struct mga_device *mdev, long clock)
{
	unsigned int vcomax, vcomin, pllreffreq;
	unsigned int delta, tmpdelta;
	unsigned int testp, testm, testn, testp2;
	unsigned int p, m, n;
	unsigned int computed;
	int i, j, tmpcount, vcount;
	bool pll_locked = false;
	u8 tmp;

	m = n = p = 0;

	delta = 0xffffffff;

	if (mdev->type == G200_EW3) {

		vcomax = 800000;
		vcomin = 400000;
		pllreffreq = 25000;

		for (testp = 1; testp < 8; testp++) {
			for (testp2 = 1; testp2 < 8; testp2++) {
				if (testp < testp2)
					continue;
				if ((clock * testp * testp2) > vcomax)
					continue;
				if ((clock * testp * testp2) < vcomin)
					continue;
				for (testm = 1; testm < 26; testm++) {
					for (testn = 32; testn < 2048 ; testn++) {
						computed = (pllreffreq * testn) /
							(testm * testp * testp2);
						if (computed > clock)
							tmpdelta = computed - clock;
						else
							tmpdelta = clock - computed;
						if (tmpdelta < delta) {
							delta = tmpdelta;
							m = ((testn & 0x100) >> 1) |
								(testm);
							n = (testn & 0xFF);
							p = ((testn & 0x600) >> 3) |
								(testp2 << 3) |
								(testp);
						}
					}
				}
			}
		}
	} else {

		vcomax = 550000;
		vcomin = 150000;
		pllreffreq = 48000;

		for (testp = 1; testp < 9; testp++) {
			if (clock * testp > vcomax)
				continue;
			if (clock * testp < vcomin)
				continue;

			for (testm = 1; testm < 17; testm++) {
				for (testn = 1; testn < 151; testn++) {
					computed = (pllreffreq * testn) /
						(testm * testp);
					if (computed > clock)
						tmpdelta = computed - clock;
					else
						tmpdelta = clock - computed;
					if (tmpdelta < delta) {
						delta = tmpdelta;
						n = testn - 1;
						m = (testm - 1) |
							((n >> 1) & 0x80);
						p = testp - 1;
					}
				}
			}
		}
	}

	for (i = 0; i <= 32 && pll_locked == false; i++) {
		if (i > 0) {
			WREG8(MGAREG_CRTC_INDEX, 0x1e);
			tmp = RREG8(MGAREG_CRTC_DATA);
			if (tmp < 0xff)
				WREG8(MGAREG_CRTC_DATA, tmp+1);
		}

		/* set pixclkdis to 1 */
		WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
		tmp = RREG8(DAC_DATA);
		tmp |= MGA1064_PIX_CLK_CTL_CLK_DIS;
		WREG8(DAC_DATA, tmp);

		WREG8(DAC_INDEX, MGA1064_REMHEADCTL);
		tmp = RREG8(DAC_DATA);
		tmp |= MGA1064_REMHEADCTL_CLKDIS;
		WREG8(DAC_DATA, tmp);

		/* select PLL Set C */
		tmp = RREG8(MGAREG_MEM_MISC_READ);
		tmp |= 0x3 << 2;
		WREG8(MGAREG_MEM_MISC_WRITE, tmp);

		WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
		tmp = RREG8(DAC_DATA);
		tmp |= MGA1064_PIX_CLK_CTL_CLK_POW_DOWN | 0x80;
		WREG8(DAC_DATA, tmp);

		udelay(500);

		/* reset the PLL */
		WREG8(DAC_INDEX, MGA1064_VREF_CTL);
		tmp = RREG8(DAC_DATA);
		tmp &= ~0x04;
		WREG8(DAC_DATA, tmp);

		udelay(50);

		/* program pixel pll register */
		WREG_DAC(MGA1064_WB_PIX_PLLC_N, n);
		WREG_DAC(MGA1064_WB_PIX_PLLC_M, m);
		WREG_DAC(MGA1064_WB_PIX_PLLC_P, p);

		udelay(50);

		/* turn pll on */
		WREG8(DAC_INDEX, MGA1064_VREF_CTL);
		tmp = RREG8(DAC_DATA);
		tmp |= 0x04;
		WREG_DAC(MGA1064_VREF_CTL, tmp);

		udelay(500);

		/* select the pixel pll */
		WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
		tmp = RREG8(DAC_DATA);
		tmp &= ~MGA1064_PIX_CLK_CTL_SEL_MSK;
		tmp |= MGA1064_PIX_CLK_CTL_SEL_PLL;
		WREG8(DAC_DATA, tmp);

		WREG8(DAC_INDEX, MGA1064_REMHEADCTL);
		tmp = RREG8(DAC_DATA);
		tmp &= ~MGA1064_REMHEADCTL_CLKSL_MSK;
		tmp |= MGA1064_REMHEADCTL_CLKSL_PLL;
		WREG8(DAC_DATA, tmp);

		/* reset dotclock rate bit */
		WREG8(MGAREG_SEQ_INDEX, 1);
		tmp = RREG8(MGAREG_SEQ_DATA);
		tmp &= ~0x8;
		WREG8(MGAREG_SEQ_DATA, tmp);

		WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
		tmp = RREG8(DAC_DATA);
		tmp &= ~MGA1064_PIX_CLK_CTL_CLK_DIS;
		WREG8(DAC_DATA, tmp);

		vcount = RREG8(MGAREG_VCOUNT);

		for (j = 0; j < 30 && pll_locked == false; j++) {
			tmpcount = RREG8(MGAREG_VCOUNT);
			if (tmpcount < vcount)
				vcount = 0;
			if ((tmpcount - vcount) > 2)
				pll_locked = true;
			else
				udelay(5);
		}
	}
	WREG8(DAC_INDEX, MGA1064_REMHEADCTL);
	tmp = RREG8(DAC_DATA);
	tmp &= ~MGA1064_REMHEADCTL_CLKDIS;
	WREG_DAC(MGA1064_REMHEADCTL, tmp);
	return 0;
}