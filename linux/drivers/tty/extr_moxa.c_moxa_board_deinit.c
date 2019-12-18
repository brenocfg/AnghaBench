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
struct moxa_board_conf {unsigned int numPorts; TYPE_1__* ports; int /*<<< orphan*/ * basemem; scalar_t__ ready; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 unsigned int MAX_PORTS_PER_BOARD ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  moxaDriver ; 
 struct moxa_board_conf* moxa_boards ; 
 int /*<<< orphan*/  moxa_lock ; 
 int /*<<< orphan*/  moxa_openlock ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ tty_port_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_tty_hangup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void moxa_board_deinit(struct moxa_board_conf *brd)
{
	unsigned int a, opened, first_idx;

	mutex_lock(&moxa_openlock);
	spin_lock_bh(&moxa_lock);
	brd->ready = 0;
	spin_unlock_bh(&moxa_lock);

	/* pci hot-un-plug support */
	for (a = 0; a < brd->numPorts; a++)
		if (tty_port_initialized(&brd->ports[a].port))
			tty_port_tty_hangup(&brd->ports[a].port, false);

	for (a = 0; a < MAX_PORTS_PER_BOARD; a++)
		tty_port_destroy(&brd->ports[a].port);

	while (1) {
		opened = 0;
		for (a = 0; a < brd->numPorts; a++)
			if (tty_port_initialized(&brd->ports[a].port))
				opened++;
		mutex_unlock(&moxa_openlock);
		if (!opened)
			break;
		msleep(50);
		mutex_lock(&moxa_openlock);
	}

	first_idx = (brd - moxa_boards) * MAX_PORTS_PER_BOARD;
	for (a = 0; a < brd->numPorts; a++)
		tty_unregister_device(moxaDriver, first_idx + a);

	iounmap(brd->basemem);
	brd->basemem = NULL;
	kfree(brd->ports);
}