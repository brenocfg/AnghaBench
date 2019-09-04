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
struct mga_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_DATA ; 
 int /*<<< orphan*/  DAC_INDEX ; 
 int /*<<< orphan*/  MGA1064_ER_PIX_PLLC_M ; 
 int /*<<< orphan*/  MGA1064_ER_PIX_PLLC_N ; 
 int /*<<< orphan*/  MGA1064_ER_PIX_PLLC_P ; 
 int MGA1064_PIX_CLK_CTL ; 
 int MGA1064_PIX_CLK_CTL_CLK_DIS ; 
 int MGA1064_PIX_CLK_CTL_CLK_POW_DOWN ; 
 int MGA1064_REMHEADCTL ; 
 int MGA1064_REMHEADCTL_CLKDIS ; 
 int /*<<< orphan*/  MGAREG_MEM_MISC_READ ; 
 int /*<<< orphan*/  MGAREG_MEM_MISC_WRITE ; 
 int RREG8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG_DAC (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mga_g200er_set_plls(struct mga_device *mdev, long clock)
{
	unsigned int vcomax, vcomin, pllreffreq;
	unsigned int delta, tmpdelta;
	int testr, testn, testm, testo;
	unsigned int p, m, n;
	unsigned int computed, vco;
	int tmp;
	const unsigned int m_div_val[] = { 1, 2, 4, 8 };

	m = n = p = 0;
	vcomax = 1488000;
	vcomin = 1056000;
	pllreffreq = 48000;

	delta = 0xffffffff;

	for (testr = 0; testr < 4; testr++) {
		if (delta == 0)
			break;
		for (testn = 5; testn < 129; testn++) {
			if (delta == 0)
				break;
			for (testm = 3; testm >= 0; testm--) {
				if (delta == 0)
					break;
				for (testo = 5; testo < 33; testo++) {
					vco = pllreffreq * (testn + 1) /
						(testr + 1);
					if (vco < vcomin)
						continue;
					if (vco > vcomax)
						continue;
					computed = vco / (m_div_val[testm] * (testo + 1));
					if (computed > clock)
						tmpdelta = computed - clock;
					else
						tmpdelta = clock - computed;
					if (tmpdelta < delta) {
						delta = tmpdelta;
						m = testm | (testo << 3);
						n = testn;
						p = testr | (testr << 3);
					}
				}
			}
		}
	}

	WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
	tmp = RREG8(DAC_DATA);
	tmp |= MGA1064_PIX_CLK_CTL_CLK_DIS;
	WREG8(DAC_DATA, tmp);

	WREG8(DAC_INDEX, MGA1064_REMHEADCTL);
	tmp = RREG8(DAC_DATA);
	tmp |= MGA1064_REMHEADCTL_CLKDIS;
	WREG8(DAC_DATA, tmp);

	tmp = RREG8(MGAREG_MEM_MISC_READ);
	tmp |= (0x3<<2) | 0xc0;
	WREG8(MGAREG_MEM_MISC_WRITE, tmp);

	WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
	tmp = RREG8(DAC_DATA);
	tmp &= ~MGA1064_PIX_CLK_CTL_CLK_DIS;
	tmp |= MGA1064_PIX_CLK_CTL_CLK_POW_DOWN;
	WREG8(DAC_DATA, tmp);

	udelay(500);

	WREG_DAC(MGA1064_ER_PIX_PLLC_N, n);
	WREG_DAC(MGA1064_ER_PIX_PLLC_M, m);
	WREG_DAC(MGA1064_ER_PIX_PLLC_P, p);

	udelay(50);

	return 0;
}