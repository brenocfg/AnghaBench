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
struct lpc32xx_udc {int /*<<< orphan*/  udp_baseaddr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int USBD_CCEMPTY ; 
 int USBD_CDFULL ; 
 int /*<<< orphan*/  USBD_CMDDATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_DEVINTCLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_DEVINTST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_protocol_cmd_w (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 udc_protocol_cmd_r(struct lpc32xx_udc *udc, u32 cmd)
{
	int to = 1000;

	/* Write a command and read data from the protocol engine */
	writel((USBD_CDFULL | USBD_CCEMPTY),
		     USBD_DEVINTCLR(udc->udp_baseaddr));

	/* Write command code */
	udc_protocol_cmd_w(udc, cmd);

	while ((!(readl(USBD_DEVINTST(udc->udp_baseaddr)) & USBD_CDFULL))
	       && (to > 0))
		to--;
	if (!to)
		dev_dbg(udc->dev,
			"Protocol engine didn't receive response (CDFULL)\n");

	return readl(USBD_CMDDATA(udc->udp_baseaddr));
}