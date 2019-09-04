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
struct hdmi_pll_8996 {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG (char*,...) ; 
 int HDMI_PLL_POLL_MAX_READS ; 
 unsigned long HDMI_PLL_POLL_TIMEOUT_US ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_C_READY_STATUS ; 
 int hdmi_pll_read (struct hdmi_pll_8996*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (unsigned long) ; 

__attribute__((used)) static int hdmi_8996_pll_lock_status(struct hdmi_pll_8996 *pll)
{
	u32 status;
	int nb_tries = HDMI_PLL_POLL_MAX_READS;
	unsigned long timeout = HDMI_PLL_POLL_TIMEOUT_US;
	int pll_locked = 0;

	DBG("Waiting for PLL lock");

	while (nb_tries--) {
		status = hdmi_pll_read(pll,
				       REG_HDMI_PHY_QSERDES_COM_C_READY_STATUS);
		pll_locked = status & BIT(0);

		if (pll_locked)
			break;

		udelay(timeout);
	}

	DBG("HDMI PLL is %slocked", pll_locked ? "" : "*not* ");

	return pll_locked;
}