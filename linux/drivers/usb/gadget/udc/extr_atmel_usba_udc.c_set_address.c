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
struct usba_udc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  DBG_BUS ; 
 int /*<<< orphan*/  DEV_ADDR ; 
 int /*<<< orphan*/  USBA_BFINS (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usba_readl (struct usba_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usba_writel (struct usba_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_address(struct usba_udc *udc, unsigned int addr)
{
	u32 regval;

	DBG(DBG_BUS, "setting address %u...\n", addr);
	regval = usba_readl(udc, CTRL);
	regval = USBA_BFINS(DEV_ADDR, addr, regval);
	usba_writel(udc, CTRL, regval);
}