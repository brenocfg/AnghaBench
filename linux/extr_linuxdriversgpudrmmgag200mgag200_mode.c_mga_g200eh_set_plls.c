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
 scalar_t__ G200_EH3 ; 
 int /*<<< orphan*/  MGA1064_EH_PIX_PLLC_M ; 
 int /*<<< orphan*/  MGA1064_EH_PIX_PLLC_N ; 
 int /*<<< orphan*/  MGA1064_EH_PIX_PLLC_P ; 
 int MGA1064_PIX_CLK_CTL ; 
 int MGA1064_PIX_CLK_CTL_CLK_DIS ; 
 int MGA1064_PIX_CLK_CTL_CLK_POW_DOWN ; 
 int MGA1064_PIX_CLK_CTL_SEL_MSK ; 
 int MGA1064_PIX_CLK_CTL_SEL_PLL ; 
 int /*<<< orphan*/  MGAREG_MEM_MISC_READ ; 
 int /*<<< orphan*/  MGAREG_MEM_MISC_WRITE ; 
 int /*<<< orphan*/  MGAREG_VCOUNT ; 
 int RREG8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG_DAC (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mga_g200eh_set_plls(struct mga_device *mdev, long clock)
{
	unsigned int vcomax, vcomin, pllreffreq;
	unsigned int delta, tmpdelta;
	unsigned int testp, testm, testn;
	unsigned int p, m, n;
	unsigned int computed;
	int i, j, tmpcount, vcount;
	u8 tmp;
	bool pll_locked = false;

	m = n = p = 0;

	if (mdev->type == G200_EH3) {
		vcomax = 3000000;
		vcomin = 1500000;
		pllreffreq = 25000;

		delta = 0xffffffff;

		testp = 0;

		for (testm = 150; testm >= 6; testm--) {
			if (clock * testm > vcomax)
				continue;
			if (clock * testm < vcomin)
				continue;
			for (testn = 120; testn >= 60; testn--) {
				computed = (pllreffreq * testn) / testm;
				if (computed > clock)
					tmpdelta = computed - clock;
				else
					tmpdelta = clock - computed;
				if (tmpdelta < delta) {
					delta = tmpdelta;
					n = testn;
					m = testm;
					p = testp;
				}
				if (delta == 0)
					break;
			}
			if (delta == 0)
				break;
		}
	} else {

		vcomax = 800000;
		vcomin = 400000;
		pllreffreq = 33333;

		delta = 0xffffffff;

		for (testp = 16; testp > 0; testp >>= 1) {
			if (clock * testp > vcomax)
				continue;
			if (clock * testp < vcomin)
				continue;

			for (testm = 1; testm < 33; testm++) {
				for (testn = 17; testn < 257; testn++) {
					computed = (pllreffreq * testn) /
						(testm * testp);
					if (computed > clock)
						tmpdelta = computed - clock;
					else
						tmpdelta = clock - computed;
					if (tmpdelta < delta) {
						delta = tmpdelta;
						n = testn - 1;
						m = (testm - 1);
						p = testp - 1;
					}
					if ((clock * testp) >= 600000)
						p |= 0x80;
				}
			}
		}
	}
	for (i = 0; i <= 32 && pll_locked == false; i++) {
		WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
		tmp = RREG8(DAC_DATA);
		tmp |= MGA1064_PIX_CLK_CTL_CLK_DIS;
		WREG8(DAC_DATA, tmp);

		tmp = RREG8(MGAREG_MEM_MISC_READ);
		tmp |= 0x3 << 2;
		WREG8(MGAREG_MEM_MISC_WRITE, tmp);

		WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
		tmp = RREG8(DAC_DATA);
		tmp |= MGA1064_PIX_CLK_CTL_CLK_POW_DOWN;
		WREG8(DAC_DATA, tmp);

		udelay(500);

		WREG_DAC(MGA1064_EH_PIX_PLLC_M, m);
		WREG_DAC(MGA1064_EH_PIX_PLLC_N, n);
		WREG_DAC(MGA1064_EH_PIX_PLLC_P, p);

		udelay(500);

		WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
		tmp = RREG8(DAC_DATA);
		tmp &= ~MGA1064_PIX_CLK_CTL_SEL_MSK;
		tmp |= MGA1064_PIX_CLK_CTL_SEL_PLL;
		WREG8(DAC_DATA, tmp);

		WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
		tmp = RREG8(DAC_DATA);
		tmp &= ~MGA1064_PIX_CLK_CTL_CLK_DIS;
		tmp &= ~MGA1064_PIX_CLK_CTL_CLK_POW_DOWN;
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

	return 0;
}