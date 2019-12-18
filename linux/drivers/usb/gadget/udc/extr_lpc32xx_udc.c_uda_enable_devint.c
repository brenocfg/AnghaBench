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
typedef  int /*<<< orphan*/  u32 ;
struct lpc32xx_udc {int /*<<< orphan*/  udp_baseaddr; int /*<<< orphan*/  enabled_devints; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_DEVINTEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void uda_enable_devint(struct lpc32xx_udc *udc, u32 devmask)
{
	udc->enabled_devints |= devmask;
	writel(udc->enabled_devints, USBD_DEVINTEN(udc->udp_baseaddr));
}