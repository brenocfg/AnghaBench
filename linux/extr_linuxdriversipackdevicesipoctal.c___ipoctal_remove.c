#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ipoctal_channel {int /*<<< orphan*/  tty_port; } ;
struct ipoctal {int /*<<< orphan*/  tty_drv; struct ipoctal_channel* channel; TYPE_3__* dev; } ;
struct TYPE_6__ {TYPE_2__* bus; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* free_irq ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int NR_CHANNELS ; 
 int /*<<< orphan*/  kfree (struct ipoctal*) ; 
 int /*<<< orphan*/  put_tty_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_free_xmit_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tty_unregister_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __ipoctal_remove(struct ipoctal *ipoctal)
{
	int i;

	ipoctal->dev->bus->ops->free_irq(ipoctal->dev);

	for (i = 0; i < NR_CHANNELS; i++) {
		struct ipoctal_channel *channel = &ipoctal->channel[i];
		tty_unregister_device(ipoctal->tty_drv, i);
		tty_port_free_xmit_buf(&channel->tty_port);
		tty_port_destroy(&channel->tty_port);
	}

	tty_unregister_driver(ipoctal->tty_drv);
	put_tty_driver(ipoctal->tty_drv);
	kfree(ipoctal);
}