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
typedef  int u32 ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  PRCM_APE_RESETN_CLR ; 
 int PRCM_APE_RESETN_DSIPLL_RESETN ; 
 int /*<<< orphan*/  PRCM_APE_RESETN_SET ; 
 int /*<<< orphan*/  PRCM_MMIP_LS_CLAMP_CLR ; 
 int PRCM_MMIP_LS_CLAMP_DSIPLL_CLAMP ; 
 int PRCM_MMIP_LS_CLAMP_DSIPLL_CLAMPI ; 
 int /*<<< orphan*/  PRCM_MMIP_LS_CLAMP_SET ; 
 int /*<<< orphan*/  PRCM_PLLDSI_ENABLE ; 
 int PRCM_PLLDSI_ENABLE_PRCM_PLLDSI_ENABLE ; 
 int plldsi_locked () ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int request_plldsi(bool enable)
{
	int r = 0;
	u32 val;

	writel((PRCM_MMIP_LS_CLAMP_DSIPLL_CLAMP |
		PRCM_MMIP_LS_CLAMP_DSIPLL_CLAMPI), (enable ?
		PRCM_MMIP_LS_CLAMP_CLR : PRCM_MMIP_LS_CLAMP_SET));

	val = readl(PRCM_PLLDSI_ENABLE);
	if (enable)
		val |= PRCM_PLLDSI_ENABLE_PRCM_PLLDSI_ENABLE;
	else
		val &= ~PRCM_PLLDSI_ENABLE_PRCM_PLLDSI_ENABLE;
	writel(val, PRCM_PLLDSI_ENABLE);

	if (enable) {
		unsigned int i;
		bool locked = plldsi_locked();

		for (i = 10; !locked && (i > 0); --i) {
			udelay(100);
			locked = plldsi_locked();
		}
		if (locked) {
			writel(PRCM_APE_RESETN_DSIPLL_RESETN,
				PRCM_APE_RESETN_SET);
		} else {
			writel((PRCM_MMIP_LS_CLAMP_DSIPLL_CLAMP |
				PRCM_MMIP_LS_CLAMP_DSIPLL_CLAMPI),
				PRCM_MMIP_LS_CLAMP_SET);
			val &= ~PRCM_PLLDSI_ENABLE_PRCM_PLLDSI_ENABLE;
			writel(val, PRCM_PLLDSI_ENABLE);
			r = -EAGAIN;
		}
	} else {
		writel(PRCM_APE_RESETN_DSIPLL_RESETN, PRCM_APE_RESETN_CLR);
	}
	return r;
}