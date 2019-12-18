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
struct niu {int /*<<< orphan*/  port; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTXMAC_SW_RST ; 
 int BTXMAC_SW_RST_RESET ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int nr64_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64_mac (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int niu_reset_tx_bmac(struct niu *np)
{
	int limit;

	nw64_mac(BTXMAC_SW_RST, BTXMAC_SW_RST_RESET);
	limit = 1000;
	while (--limit >= 0) {
		if (!(nr64_mac(BTXMAC_SW_RST) & BTXMAC_SW_RST_RESET))
			break;
		udelay(100);
	}
	if (limit < 0) {
		dev_err(np->device, "Port %u TX BMAC would not reset, BTXMAC_SW_RST[%llx]\n",
			np->port,
			(unsigned long long) nr64_mac(BTXMAC_SW_RST));
		return -ENODEV;
	}

	return 0;
}