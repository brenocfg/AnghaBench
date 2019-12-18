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
typedef  int u32 ;
struct vme_slave_resource {unsigned int number; struct vme_bridge* parent; } ;
struct vme_bridge {int /*<<< orphan*/  parent; struct ca91cx42_driver* driver_priv; } ;
struct ca91cx42_driver {scalar_t__ base; } ;
typedef  unsigned long long dma_addr_t ;

/* Variables and functions */
 scalar_t__* CA91CX42_VSI_BD ; 
 scalar_t__* CA91CX42_VSI_BS ; 
 scalar_t__* CA91CX42_VSI_CTL ; 
 unsigned int CA91CX42_VSI_CTL_EN ; 
 unsigned int CA91CX42_VSI_CTL_PGM_DATA ; 
 unsigned int CA91CX42_VSI_CTL_PGM_M ; 
 unsigned int CA91CX42_VSI_CTL_PGM_PGM ; 
 unsigned int CA91CX42_VSI_CTL_SUPER_M ; 
 unsigned int CA91CX42_VSI_CTL_SUPER_NPRIV ; 
 unsigned int CA91CX42_VSI_CTL_SUPER_SUPR ; 
 unsigned int CA91CX42_VSI_CTL_VAS_A16 ; 
 unsigned int CA91CX42_VSI_CTL_VAS_A24 ; 
 unsigned int CA91CX42_VSI_CTL_VAS_A32 ; 
 unsigned int CA91CX42_VSI_CTL_VAS_M ; 
 unsigned int CA91CX42_VSI_CTL_VAS_USER1 ; 
 unsigned int CA91CX42_VSI_CTL_VAS_USER2 ; 
 scalar_t__* CA91CX42_VSI_TO ; 
 int EINVAL ; 
#define  VME_A16 136 
#define  VME_A24 135 
#define  VME_A32 134 
#define  VME_A64 133 
#define  VME_CRCSR 132 
 int VME_DATA ; 
 int VME_PROG ; 
 int VME_SUPER ; 
 int VME_USER ; 
#define  VME_USER1 131 
#define  VME_USER2 130 
#define  VME_USER3 129 
#define  VME_USER4 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (unsigned int,scalar_t__) ; 

__attribute__((used)) static int ca91cx42_slave_set(struct vme_slave_resource *image, int enabled,
	unsigned long long vme_base, unsigned long long size,
	dma_addr_t pci_base, u32 aspace, u32 cycle)
{
	unsigned int i, addr = 0, granularity;
	unsigned int temp_ctl = 0;
	unsigned int vme_bound, pci_offset;
	struct vme_bridge *ca91cx42_bridge;
	struct ca91cx42_driver *bridge;

	ca91cx42_bridge = image->parent;

	bridge = ca91cx42_bridge->driver_priv;

	i = image->number;

	switch (aspace) {
	case VME_A16:
		addr |= CA91CX42_VSI_CTL_VAS_A16;
		break;
	case VME_A24:
		addr |= CA91CX42_VSI_CTL_VAS_A24;
		break;
	case VME_A32:
		addr |= CA91CX42_VSI_CTL_VAS_A32;
		break;
	case VME_USER1:
		addr |= CA91CX42_VSI_CTL_VAS_USER1;
		break;
	case VME_USER2:
		addr |= CA91CX42_VSI_CTL_VAS_USER2;
		break;
	case VME_A64:
	case VME_CRCSR:
	case VME_USER3:
	case VME_USER4:
	default:
		dev_err(ca91cx42_bridge->parent, "Invalid address space\n");
		return -EINVAL;
		break;
	}

	/*
	 * Bound address is a valid address for the window, adjust
	 * accordingly
	 */
	vme_bound = vme_base + size;
	pci_offset = pci_base - vme_base;

	if ((i == 0) || (i == 4))
		granularity = 0x1000;
	else
		granularity = 0x10000;

	if (vme_base & (granularity - 1)) {
		dev_err(ca91cx42_bridge->parent, "Invalid VME base "
			"alignment\n");
		return -EINVAL;
	}
	if (vme_bound & (granularity - 1)) {
		dev_err(ca91cx42_bridge->parent, "Invalid VME bound "
			"alignment\n");
		return -EINVAL;
	}
	if (pci_offset & (granularity - 1)) {
		dev_err(ca91cx42_bridge->parent, "Invalid PCI Offset "
			"alignment\n");
		return -EINVAL;
	}

	/* Disable while we are mucking around */
	temp_ctl = ioread32(bridge->base + CA91CX42_VSI_CTL[i]);
	temp_ctl &= ~CA91CX42_VSI_CTL_EN;
	iowrite32(temp_ctl, bridge->base + CA91CX42_VSI_CTL[i]);

	/* Setup mapping */
	iowrite32(vme_base, bridge->base + CA91CX42_VSI_BS[i]);
	iowrite32(vme_bound, bridge->base + CA91CX42_VSI_BD[i]);
	iowrite32(pci_offset, bridge->base + CA91CX42_VSI_TO[i]);

	/* Setup address space */
	temp_ctl &= ~CA91CX42_VSI_CTL_VAS_M;
	temp_ctl |= addr;

	/* Setup cycle types */
	temp_ctl &= ~(CA91CX42_VSI_CTL_PGM_M | CA91CX42_VSI_CTL_SUPER_M);
	if (cycle & VME_SUPER)
		temp_ctl |= CA91CX42_VSI_CTL_SUPER_SUPR;
	if (cycle & VME_USER)
		temp_ctl |= CA91CX42_VSI_CTL_SUPER_NPRIV;
	if (cycle & VME_PROG)
		temp_ctl |= CA91CX42_VSI_CTL_PGM_PGM;
	if (cycle & VME_DATA)
		temp_ctl |= CA91CX42_VSI_CTL_PGM_DATA;

	/* Write ctl reg without enable */
	iowrite32(temp_ctl, bridge->base + CA91CX42_VSI_CTL[i]);

	if (enabled)
		temp_ctl |= CA91CX42_VSI_CTL_EN;

	iowrite32(temp_ctl, bridge->base + CA91CX42_VSI_CTL[i]);

	return 0;
}