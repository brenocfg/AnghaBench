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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct lpc32xx_udc {int /*<<< orphan*/  udp_baseaddr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CTRL_RD_EN ; 
 int PKT_LNGTH_MASK ; 
 int PKT_RDY ; 
 int /*<<< orphan*/  USBD_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_RXPLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_clr_buffer_hwep (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  udc_pop_fifo (struct lpc32xx_udc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 udc_read_hwep(struct lpc32xx_udc *udc, u32 hwep, u32 *data,
			 u32 bytes)
{
	u32 tmpv;
	int to = 1000;
	u32 tmp, hwrep = ((hwep & 0x1E) << 1) | CTRL_RD_EN;

	/* Setup read of endpoint */
	writel(hwrep, USBD_CTRL(udc->udp_baseaddr));

	/* Wait until packet is ready */
	while ((((tmpv = readl(USBD_RXPLEN(udc->udp_baseaddr))) &
		 PKT_RDY) == 0)	&& (to > 0))
		to--;
	if (!to)
		dev_dbg(udc->dev, "No packet ready on FIFO EP read\n");

	/* Mask out count */
	tmp = tmpv & PKT_LNGTH_MASK;
	if (bytes < tmp)
		tmp = bytes;

	if ((tmp > 0) && (data != NULL))
		udc_pop_fifo(udc, (u8 *) data, tmp);

	writel(((hwep & 0x1E) << 1), USBD_CTRL(udc->udp_baseaddr));

	/* Clear the buffer */
	udc_clr_buffer_hwep(udc, hwep);

	return tmp;
}