#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct zorro_device_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  er_SerialNumber; } ;
struct TYPE_3__ {unsigned long start; } ;
struct zorro_dev {TYPE_2__ rom; TYPE_1__ resource; } ;
struct resource {int /*<<< orphan*/  name; } ;
struct net_device {int* dev_addr; unsigned long base_addr; unsigned long mem_start; int mem_end; int watchdog_timeo; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  name; } ;
struct ariadne_private {int dummy; } ;
struct Am79C960 {int dummy; } ;

/* Variables and functions */
 unsigned long ARIADNE_LANCE ; 
 unsigned long ARIADNE_RAM ; 
 int ARIADNE_RAM_SIZE ; 
 int EBUSY ; 
 int ENOMEM ; 
 int HZ ; 
 scalar_t__ ZTWO_VADDR (unsigned long) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  ariadne_netdev_ops ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,unsigned long,int*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  release_mem_region (unsigned long,int) ; 
 struct resource* request_mem_region (unsigned long,int,char*) ; 
 int /*<<< orphan*/  zorro_set_drvdata (struct zorro_dev*,struct net_device*) ; 

__attribute__((used)) static int ariadne_init_one(struct zorro_dev *z,
			    const struct zorro_device_id *ent)
{
	unsigned long board = z->resource.start;
	unsigned long base_addr = board + ARIADNE_LANCE;
	unsigned long mem_start = board + ARIADNE_RAM;
	struct resource *r1, *r2;
	struct net_device *dev;
	u32 serial;
	int err;

	r1 = request_mem_region(base_addr, sizeof(struct Am79C960), "Am79C960");
	if (!r1)
		return -EBUSY;
	r2 = request_mem_region(mem_start, ARIADNE_RAM_SIZE, "RAM");
	if (!r2) {
		release_mem_region(base_addr, sizeof(struct Am79C960));
		return -EBUSY;
	}

	dev = alloc_etherdev(sizeof(struct ariadne_private));
	if (dev == NULL) {
		release_mem_region(base_addr, sizeof(struct Am79C960));
		release_mem_region(mem_start, ARIADNE_RAM_SIZE);
		return -ENOMEM;
	}

	r1->name = dev->name;
	r2->name = dev->name;

	serial = be32_to_cpu(z->rom.er_SerialNumber);
	dev->dev_addr[0] = 0x00;
	dev->dev_addr[1] = 0x60;
	dev->dev_addr[2] = 0x30;
	dev->dev_addr[3] = (serial >> 16) & 0xff;
	dev->dev_addr[4] = (serial >> 8) & 0xff;
	dev->dev_addr[5] = serial & 0xff;
	dev->base_addr = (unsigned long)ZTWO_VADDR(base_addr);
	dev->mem_start = (unsigned long)ZTWO_VADDR(mem_start);
	dev->mem_end = dev->mem_start + ARIADNE_RAM_SIZE;

	dev->netdev_ops = &ariadne_netdev_ops;
	dev->watchdog_timeo = 5 * HZ;

	err = register_netdev(dev);
	if (err) {
		release_mem_region(base_addr, sizeof(struct Am79C960));
		release_mem_region(mem_start, ARIADNE_RAM_SIZE);
		free_netdev(dev);
		return err;
	}
	zorro_set_drvdata(z, dev);

	netdev_info(dev, "Ariadne at 0x%08lx, Ethernet Address %pM\n",
		    board, dev->dev_addr);

	return 0;
}