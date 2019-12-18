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
struct lpc32xx_udc {int /*<<< orphan*/  udp_baseaddr; } ;

/* Variables and functions */
 int USBD_CCEMPTY ; 
 int /*<<< orphan*/  USBD_CMDCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_DEVINTCLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_DEVINTST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udc_protocol_cmd_w(struct lpc32xx_udc *udc, u32 cmd)
{
	u32 pass = 0;
	int to;

	/* EP may lock on CLRI if this read isn't done */
	u32 tmp = readl(USBD_DEVINTST(udc->udp_baseaddr));
	(void) tmp;

	while (pass == 0) {
		writel(USBD_CCEMPTY, USBD_DEVINTCLR(udc->udp_baseaddr));

		/* Write command code */
		writel(cmd, USBD_CMDCODE(udc->udp_baseaddr));
		to = 10000;
		while (((readl(USBD_DEVINTST(udc->udp_baseaddr)) &
			 USBD_CCEMPTY) == 0) && (to > 0)) {
			to--;
		}

		if (to > 0)
			pass = 1;

		cpu_relax();
	}
}