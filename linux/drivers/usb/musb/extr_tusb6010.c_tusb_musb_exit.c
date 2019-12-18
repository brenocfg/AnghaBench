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
struct musb {int /*<<< orphan*/  xceiv; int /*<<< orphan*/  sync_va; int /*<<< orphan*/  (* board_set_power ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  dev_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * the_musb ; 
 int /*<<< orphan*/  usb_put_phy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tusb_musb_exit(struct musb *musb)
{
	del_timer_sync(&musb->dev_timer);
	the_musb = NULL;

	if (musb->board_set_power)
		musb->board_set_power(0);

	iounmap(musb->sync_va);

	usb_put_phy(musb->xceiv);
	return 0;
}