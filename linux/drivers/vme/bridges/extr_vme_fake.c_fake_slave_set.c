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
typedef  int u32 ;
struct vme_slave_resource {unsigned int number; int /*<<< orphan*/  mtx; struct vme_bridge* parent; } ;
struct vme_bridge {struct fake_driver* driver_priv; } ;
struct fake_driver {TYPE_1__* slaves; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int enabled; unsigned long long vme_base; unsigned long long size; int aspace; int cycle; int /*<<< orphan*/  buf_base; } ;

/* Variables and functions */
 int EINVAL ; 
#define  VME_A16 136 
#define  VME_A24 135 
#define  VME_A32 134 
#define  VME_A64 133 
#define  VME_CRCSR 132 
#define  VME_USER1 131 
#define  VME_USER2 130 
#define  VME_USER3 129 
#define  VME_USER4 128 
 int /*<<< orphan*/  fake_pci_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int fake_slave_set(struct vme_slave_resource *image, int enabled,
		unsigned long long vme_base, unsigned long long size,
		dma_addr_t buf_base, u32 aspace, u32 cycle)
{
	unsigned int i, granularity = 0;
	unsigned long long vme_bound;
	struct vme_bridge *fake_bridge;
	struct fake_driver *bridge;

	fake_bridge = image->parent;
	bridge = fake_bridge->driver_priv;

	i = image->number;

	switch (aspace) {
	case VME_A16:
		granularity = 0x10;
		break;
	case VME_A24:
		granularity = 0x1000;
		break;
	case VME_A32:
		granularity = 0x10000;
		break;
	case VME_A64:
		granularity = 0x10000;
		break;
	case VME_CRCSR:
	case VME_USER1:
	case VME_USER2:
	case VME_USER3:
	case VME_USER4:
	default:
		pr_err("Invalid address space\n");
		return -EINVAL;
	}

	/*
	 * Bound address is a valid address for the window, adjust
	 * accordingly
	 */
	vme_bound = vme_base + size - granularity;

	if (vme_base & (granularity - 1)) {
		pr_err("Invalid VME base alignment\n");
		return -EINVAL;
	}
	if (vme_bound & (granularity - 1)) {
		pr_err("Invalid VME bound alignment\n");
		return -EINVAL;
	}

	mutex_lock(&image->mtx);

	bridge->slaves[i].enabled = enabled;
	bridge->slaves[i].vme_base = vme_base;
	bridge->slaves[i].size = size;
	bridge->slaves[i].buf_base = fake_pci_to_ptr(buf_base);
	bridge->slaves[i].aspace = aspace;
	bridge->slaves[i].cycle = cycle;

	mutex_unlock(&image->mtx);

	return 0;
}