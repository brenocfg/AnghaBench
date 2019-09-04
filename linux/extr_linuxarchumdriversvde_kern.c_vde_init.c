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
struct vde_init {char* vde_switch; char* descr; } ;
struct vde_data {char* vde_switch; char* descr; struct net_device* dev; int /*<<< orphan*/ * conn; int /*<<< orphan*/ * args; } ;
struct uml_net_private {scalar_t__ user; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct uml_net_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  vde_init_libstuff (struct vde_data*,struct vde_init*) ; 

__attribute__((used)) static void vde_init(struct net_device *dev, void *data)
{
	struct vde_init *init = data;
	struct uml_net_private *pri;
	struct vde_data *vpri;

	pri = netdev_priv(dev);
	vpri = (struct vde_data *) pri->user;

	vpri->vde_switch = init->vde_switch;
	vpri->descr = init->descr ? init->descr : "UML vde_transport";
	vpri->args = NULL;
	vpri->conn = NULL;
	vpri->dev = dev;

	printk("vde backend - %s, ", vpri->vde_switch ?
	       vpri->vde_switch : "(default socket)");

	vde_init_libstuff(vpri, init);

	printk("\n");
}