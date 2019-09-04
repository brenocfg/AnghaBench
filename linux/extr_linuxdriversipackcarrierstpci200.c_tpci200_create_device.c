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
struct tpci200_board {scalar_t__* mod_mem; TYPE_1__* info; } ;
struct ipack_device {int slot; TYPE_2__* region; int /*<<< orphan*/  release; int /*<<< orphan*/  bus; } ;
typedef  enum ipack_space { ____Placeholder_ipack_space } ipack_space ;
struct TYPE_4__ {int /*<<< orphan*/  size; scalar_t__ start; } ;
struct TYPE_3__ {int /*<<< orphan*/  ipack_bus; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IPACK_SPACE_COUNT ; 
 int ipack_device_add (struct ipack_device*) ; 
 int ipack_device_init (struct ipack_device*) ; 
 int /*<<< orphan*/  ipack_put_device (struct ipack_device*) ; 
 struct ipack_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpci200_release_device ; 
 int* tpci200_space_interval ; 
 int /*<<< orphan*/ * tpci200_space_size ; 

__attribute__((used)) static int tpci200_create_device(struct tpci200_board *tpci200, int i)
{
	int ret;
	enum ipack_space space;
	struct ipack_device *dev =
		kzalloc(sizeof(struct ipack_device), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;
	dev->slot = i;
	dev->bus = tpci200->info->ipack_bus;
	dev->release = tpci200_release_device;

	for (space = 0; space < IPACK_SPACE_COUNT; space++) {
		dev->region[space].start =
			tpci200->mod_mem[space]
			+ tpci200_space_interval[space] * i;
		dev->region[space].size = tpci200_space_size[space];
	}

	ret = ipack_device_init(dev);
	if (ret < 0) {
		ipack_put_device(dev);
		return ret;
	}

	ret = ipack_device_add(dev);
	if (ret < 0)
		ipack_put_device(dev);

	return ret;
}