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
struct nozomi {TYPE_1__* port; scalar_t__ index_start; scalar_t__ open_ttys; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG1 (char*) ; 
 unsigned int MAX_PORT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ntty_driver ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_tty_hangup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tty_exit(struct nozomi *dc)
{
	unsigned int i;

	DBG1(" ");

	for (i = 0; i < MAX_PORT; ++i)
		tty_port_tty_hangup(&dc->port[i].port, false);

	/* Racy below - surely should wait for scheduled work to be done or
	   complete off a hangup method ? */
	while (dc->open_ttys)
		msleep(1);
	for (i = 0; i < MAX_PORT; ++i) {
		tty_unregister_device(ntty_driver, dc->index_start + i);
		tty_port_destroy(&dc->port[i].port);
	}
}