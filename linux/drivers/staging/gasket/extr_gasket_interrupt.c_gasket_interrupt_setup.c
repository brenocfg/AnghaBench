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
typedef  int ulong ;
struct gasket_interrupt_data {int num_interrupts; int pack_width; TYPE_1__* interrupts; int /*<<< orphan*/  interrupt_bar_index; } ;
struct gasket_dev {int /*<<< orphan*/  dev; struct gasket_interrupt_data* interrupt_data; } ;
struct TYPE_2__ {int index; int packing; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
#define  PACK_0 131 
#define  PACK_1 130 
#define  PACK_2 129 
#define  PACK_3 128 
 int UNPACKED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int gasket_dev_read_64 (struct gasket_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gasket_dev_write_64 (struct gasket_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gasket_interrupt_setup(struct gasket_dev *gasket_dev)
{
	int i;
	int pack_shift;
	ulong mask;
	ulong value;
	struct gasket_interrupt_data *interrupt_data =
		gasket_dev->interrupt_data;

	if (!interrupt_data) {
		dev_dbg(gasket_dev->dev, "Interrupt data is not initialized\n");
		return;
	}

	dev_dbg(gasket_dev->dev, "Running interrupt setup\n");

	/* Setup the MSIX table. */

	for (i = 0; i < interrupt_data->num_interrupts; i++) {
		/*
		 * If the interrupt is not packed, we can write the index into
		 * the register directly. If not, we need to deal with a read-
		 * modify-write and shift based on the packing index.
		 */
		dev_dbg(gasket_dev->dev,
			"Setting up interrupt index %d with index 0x%llx and packing %d\n",
			interrupt_data->interrupts[i].index,
			interrupt_data->interrupts[i].reg,
			interrupt_data->interrupts[i].packing);
		if (interrupt_data->interrupts[i].packing == UNPACKED) {
			value = interrupt_data->interrupts[i].index;
		} else {
			switch (interrupt_data->interrupts[i].packing) {
			case PACK_0:
				pack_shift = 0;
				break;
			case PACK_1:
				pack_shift = interrupt_data->pack_width;
				break;
			case PACK_2:
				pack_shift = 2 * interrupt_data->pack_width;
				break;
			case PACK_3:
				pack_shift = 3 * interrupt_data->pack_width;
				break;
			default:
				dev_dbg(gasket_dev->dev,
					"Found interrupt description with unknown enum %d\n",
					interrupt_data->interrupts[i].packing);
				return;
			}

			mask = ~(0xFFFF << pack_shift);
			value = gasket_dev_read_64(gasket_dev,
						   interrupt_data->interrupt_bar_index,
						   interrupt_data->interrupts[i].reg);
			value &= mask;
			value |= interrupt_data->interrupts[i].index
				 << pack_shift;
		}
		gasket_dev_write_64(gasket_dev, value,
				    interrupt_data->interrupt_bar_index,
				    interrupt_data->interrupts[i].reg);
	}
}