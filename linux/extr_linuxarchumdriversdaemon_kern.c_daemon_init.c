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
struct uml_net_private {scalar_t__ user; } ;
struct net_device {int dummy; } ;
struct daemon_init {int /*<<< orphan*/  ctl_sock; int /*<<< orphan*/  sock_type; } ;
struct daemon_data {int fd; int control; int /*<<< orphan*/  ctl_sock; int /*<<< orphan*/  sock_type; int /*<<< orphan*/ * local_addr; int /*<<< orphan*/ * data_addr; int /*<<< orphan*/ * ctl_addr; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCH_VERSION ; 
 struct uml_net_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void daemon_init(struct net_device *dev, void *data)
{
	struct uml_net_private *pri;
	struct daemon_data *dpri;
	struct daemon_init *init = data;

	pri = netdev_priv(dev);
	dpri = (struct daemon_data *) pri->user;
	dpri->sock_type = init->sock_type;
	dpri->ctl_sock = init->ctl_sock;
	dpri->fd = -1;
	dpri->control = -1;
	dpri->dev = dev;
	/* We will free this pointer. If it contains crap we're burned. */
	dpri->ctl_addr = NULL;
	dpri->data_addr = NULL;
	dpri->local_addr = NULL;

	printk("daemon backend (uml_switch version %d) - %s:%s",
	       SWITCH_VERSION, dpri->sock_type, dpri->ctl_sock);
	printk("\n");
}