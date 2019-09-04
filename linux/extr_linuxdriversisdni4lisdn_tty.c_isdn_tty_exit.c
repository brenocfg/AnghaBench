#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * xmit_buf; } ;
struct TYPE_7__ {TYPE_3__ port; } ;
typedef  TYPE_2__ modem_info ;
struct TYPE_6__ {int /*<<< orphan*/ * tty_modem; TYPE_2__* info; } ;
struct TYPE_9__ {TYPE_1__ mdm; } ;

/* Variables and functions */
 int ISDN_MAX_CHANNELS ; 
 TYPE_5__* dev ; 
 int /*<<< orphan*/  isdn_tty_cleanup_xmit (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_tty_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_destroy (TYPE_3__*) ; 
 int /*<<< orphan*/  tty_unregister_driver (int /*<<< orphan*/ *) ; 

void
isdn_tty_exit(void)
{
	modem_info *info;
	int i;

	for (i = 0; i < ISDN_MAX_CHANNELS; i++) {
		info = &dev->mdm.info[i];
		isdn_tty_cleanup_xmit(info);
#ifdef CONFIG_ISDN_TTY_FAX
		kfree(info->fax);
#endif
		kfree(info->port.xmit_buf - 4);
		info->port.xmit_buf = NULL;
		tty_port_destroy(&info->port);
	}
	tty_unregister_driver(dev->mdm.tty_modem);
	put_tty_driver(dev->mdm.tty_modem);
	dev->mdm.tty_modem = NULL;
}