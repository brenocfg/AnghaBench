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
struct nubus_rsrc {struct nubus_board* board; } ;
struct nubus_dirent {int dummy; } ;
struct nubus_dir {int dummy; } ;
struct nubus_board {int slot; int slot_addr; int /*<<< orphan*/  dev; } ;
struct net_device {int base_addr; int* dev_addr; int mem_start; int mem_end; int /*<<< orphan*/  irq; } ;
typedef  enum mac8390_type { ____Placeholder_mac8390_type } mac8390_type ;

/* Variables and functions */
 int /*<<< orphan*/  CABLETRON_8390_BASE ; 
 int /*<<< orphan*/  CABLETRON_8390_MEM ; 
 int /*<<< orphan*/  DAYNA_8390_BASE ; 
 int /*<<< orphan*/  DAYNA_8390_MEM ; 
 int /*<<< orphan*/  INTERLAN_8390_BASE ; 
 int /*<<< orphan*/  INTERLAN_8390_MEM ; 
#define  MAC8390_CABLETRON 131 
#define  MAC8390_DAYNA 130 
#define  MAC8390_INTERLAN 129 
#define  MAC8390_KINETICS 128 
 int /*<<< orphan*/  NUBUS_RESID_MAC_ADDRESS ; 
 int /*<<< orphan*/  NUBUS_RESID_MINOR_BASEOS ; 
 int /*<<< orphan*/  NUBUS_RESID_MINOR_LENGTH ; 
 int /*<<< orphan*/  SLOT2IRQ (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int mac8390_memsize (int) ; 
 int nubus_find_rsrc (struct nubus_dir*,int /*<<< orphan*/ ,struct nubus_dirent*) ; 
 int nubus_get_func_dir (struct nubus_rsrc*,struct nubus_dir*) ; 
 int /*<<< orphan*/  nubus_get_rsrc_mem (int*,struct nubus_dirent*,int) ; 
 int /*<<< orphan*/  nubus_rewinddir (struct nubus_dir*) ; 
 int* useresources ; 

__attribute__((used)) static bool mac8390_rsrc_init(struct net_device *dev,
			      struct nubus_rsrc *fres,
			      enum mac8390_type cardtype)
{
	struct nubus_board *board = fres->board;
	struct nubus_dir dir;
	struct nubus_dirent ent;
	int offset;
	volatile unsigned short *i;

	dev->irq = SLOT2IRQ(board->slot);
	/* This is getting to be a habit */
	dev->base_addr = board->slot_addr | ((board->slot & 0xf) << 20);

	/*
	 * Get some Nubus info - we will trust the card's idea
	 * of where its memory and registers are.
	 */

	if (nubus_get_func_dir(fres, &dir) == -1) {
		dev_err(&board->dev,
			"Unable to get Nubus functional directory\n");
		return false;
	}

	/* Get the MAC address */
	if (nubus_find_rsrc(&dir, NUBUS_RESID_MAC_ADDRESS, &ent) == -1) {
		dev_info(&board->dev, "MAC address resource not found\n");
		return false;
	}

	nubus_get_rsrc_mem(dev->dev_addr, &ent, 6);

	if (useresources[cardtype] == 1) {
		nubus_rewinddir(&dir);
		if (nubus_find_rsrc(&dir, NUBUS_RESID_MINOR_BASEOS,
				    &ent) == -1) {
			dev_err(&board->dev,
				"Memory offset resource not found\n");
			return false;
		}
		nubus_get_rsrc_mem(&offset, &ent, 4);
		dev->mem_start = dev->base_addr + offset;
		/* yes, this is how the Apple driver does it */
		dev->base_addr = dev->mem_start + 0x10000;
		nubus_rewinddir(&dir);
		if (nubus_find_rsrc(&dir, NUBUS_RESID_MINOR_LENGTH,
				    &ent) == -1) {
			dev_info(&board->dev,
				 "Memory length resource not found, probing\n");
			offset = mac8390_memsize(dev->mem_start);
		} else {
			nubus_get_rsrc_mem(&offset, &ent, 4);
		}
		dev->mem_end = dev->mem_start + offset;
	} else {
		switch (cardtype) {
		case MAC8390_KINETICS:
		case MAC8390_DAYNA: /* it's the same */
			dev->base_addr = (int)(board->slot_addr +
					       DAYNA_8390_BASE);
			dev->mem_start = (int)(board->slot_addr +
					       DAYNA_8390_MEM);
			dev->mem_end = dev->mem_start +
				       mac8390_memsize(dev->mem_start);
			break;
		case MAC8390_INTERLAN:
			dev->base_addr = (int)(board->slot_addr +
					       INTERLAN_8390_BASE);
			dev->mem_start = (int)(board->slot_addr +
					       INTERLAN_8390_MEM);
			dev->mem_end = dev->mem_start +
				       mac8390_memsize(dev->mem_start);
			break;
		case MAC8390_CABLETRON:
			dev->base_addr = (int)(board->slot_addr +
					       CABLETRON_8390_BASE);
			dev->mem_start = (int)(board->slot_addr +
					       CABLETRON_8390_MEM);
			/* The base address is unreadable if 0x00
			 * has been written to the command register
			 * Reset the chip by writing E8390_NODMA +
			 *   E8390_PAGE0 + E8390_STOP just to be
			 *   sure
			 */
			i = (void *)dev->base_addr;
			*i = 0x21;
			dev->mem_end = dev->mem_start +
				       mac8390_memsize(dev->mem_start);
			break;

		default:
			dev_err(&board->dev,
				"No known base address for card type\n");
			return false;
		}
	}

	return true;
}