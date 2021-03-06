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
struct sta2x11_vip {int /*<<< orphan*/  slock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVP_CTL ; 
 int /*<<< orphan*/  DVP_CTL_RST ; 
 int /*<<< orphan*/  DVP_HLFLN ; 
 int /*<<< orphan*/  DVP_HLFLN_SD ; 
 int /*<<< orphan*/  DVP_ITS ; 
 int /*<<< orphan*/  reg_read (struct sta2x11_vip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct sta2x11_vip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sta2x11_vip_init_register(struct sta2x11_vip *vip)
{
	/* Register initialization */
	spin_lock_irq(&vip->slock);
	/* Clean interrupt */
	reg_read(vip, DVP_ITS);
	/* Enable Half Line per vertical */
	reg_write(vip, DVP_HLFLN, DVP_HLFLN_SD);
	/* Reset VIP control */
	reg_write(vip, DVP_CTL, DVP_CTL_RST);
	/* Clear VIP control */
	reg_write(vip, DVP_CTL, 0);
	spin_unlock_irq(&vip->slock);
}