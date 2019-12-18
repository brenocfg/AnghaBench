#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  (* busctl_offset ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct musb {TYPE_1__ io; int /*<<< orphan*/  mregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_TXFUNCADDR ; 
 int /*<<< orphan*/  musb_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void musb_write_txfunaddr(struct musb *musb, u8 epnum,
		u8 qh_addr_reg)
{
	musb_writeb(musb->mregs,
		    musb->io.busctl_offset(epnum, MUSB_TXFUNCADDR),
		    qh_addr_reg);
}