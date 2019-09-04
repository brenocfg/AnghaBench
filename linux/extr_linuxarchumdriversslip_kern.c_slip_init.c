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
struct slip_init {int /*<<< orphan*/  gate_addr; } ;
struct slip_data {int slave; int /*<<< orphan*/  gate_addr; int /*<<< orphan*/  slip; struct net_device* dev; int /*<<< orphan*/ * addr; int /*<<< orphan*/  name; } ;
struct net_device {int tx_queue_len; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; scalar_t__ addr_len; int /*<<< orphan*/ * header_ops; scalar_t__ hard_header_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_SLIP ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct uml_net_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slip_proto_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void slip_init(struct net_device *dev, void *data)
{
	struct uml_net_private *private;
	struct slip_data *spri;
	struct slip_init *init = data;

	private = netdev_priv(dev);
	spri = (struct slip_data *) private->user;

	memset(spri->name, 0, sizeof(spri->name));
	spri->addr = NULL;
	spri->gate_addr = init->gate_addr;
	spri->slave = -1;
	spri->dev = dev;

	slip_proto_init(&spri->slip);

	dev->hard_header_len = 0;
	dev->header_ops = NULL;
	dev->addr_len = 0;
	dev->type = ARPHRD_SLIP;
	dev->tx_queue_len = 256;
	dev->flags = IFF_NOARP;
	printk("SLIP backend - SLIP IP = %s\n", spri->gate_addr);
}