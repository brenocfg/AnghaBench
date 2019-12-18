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
struct lpc32xx_udc {int /*<<< orphan*/  udp_baseaddr; } ;

/* Variables and functions */
 int CTRL_WR_EN ; 
 int /*<<< orphan*/  USBD_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_TXDATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_TXPLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_stuff_fifo (struct lpc32xx_udc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  udc_val_buffer_hwep (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udc_write_hwep(struct lpc32xx_udc *udc, u32 hwep, u32 *data,
			   u32 bytes)
{
	u32 hwwep = ((hwep & 0x1E) << 1) | CTRL_WR_EN;

	if ((bytes > 0) && (data == NULL))
		return;

	/* Setup write of endpoint */
	writel(hwwep, USBD_CTRL(udc->udp_baseaddr));

	writel(bytes, USBD_TXPLEN(udc->udp_baseaddr));

	/* Need at least 1 byte to trigger TX */
	if (bytes == 0)
		writel(0, USBD_TXDATA(udc->udp_baseaddr));
	else
		udc_stuff_fifo(udc, (u8 *) data, bytes);

	writel(((hwep & 0x1E) << 1), USBD_CTRL(udc->udp_baseaddr));

	udc_val_buffer_hwep(udc, hwep);
}