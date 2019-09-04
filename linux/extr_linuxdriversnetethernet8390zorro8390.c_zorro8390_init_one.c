#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct zorro_device_id {int dummy; } ;
struct TYPE_4__ {unsigned long start; } ;
struct zorro_dev {scalar_t__ id; TYPE_1__ resource; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {scalar_t__ id; unsigned long offset; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int NE_IO_EXTENT ; 
 int /*<<< orphan*/  ZTWO_VADDR (unsigned long) ; 
 struct net_device* ____alloc_ei_netdev (int /*<<< orphan*/ ) ; 
 TYPE_2__* cards ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  release_mem_region (unsigned long,int) ; 
 int /*<<< orphan*/  request_mem_region (unsigned long,int,int /*<<< orphan*/ ) ; 
 int zorro8390_init (struct net_device*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zorro_set_drvdata (struct zorro_dev*,struct net_device*) ; 

__attribute__((used)) static int zorro8390_init_one(struct zorro_dev *z,
			      const struct zorro_device_id *ent)
{
	struct net_device *dev;
	unsigned long board, ioaddr;
	int err, i;

	for (i = ARRAY_SIZE(cards) - 1; i >= 0; i--)
		if (z->id == cards[i].id)
			break;
	if (i < 0)
		return -ENODEV;

	board = z->resource.start;
	ioaddr = board + cards[i].offset;
	dev = ____alloc_ei_netdev(0);
	if (!dev)
		return -ENOMEM;
	if (!request_mem_region(ioaddr, NE_IO_EXTENT * 2, DRV_NAME)) {
		free_netdev(dev);
		return -EBUSY;
	}
	err = zorro8390_init(dev, board, cards[i].name, ZTWO_VADDR(ioaddr));
	if (err) {
		release_mem_region(ioaddr, NE_IO_EXTENT * 2);
		free_netdev(dev);
		return err;
	}
	zorro_set_drvdata(z, dev);
	return 0;
}