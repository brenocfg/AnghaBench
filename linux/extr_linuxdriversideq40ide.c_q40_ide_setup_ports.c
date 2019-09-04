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
struct TYPE_2__ {void* ctl_addr; void* status_addr; void* device_addr; void* lbah_addr; void* lbam_addr; void* lbal_addr; void* nsect_addr; void* error_addr; int /*<<< orphan*/  data_addr; } ;
struct ide_hw {int irq; TYPE_1__ io_ports; } ;

/* Variables and functions */
 void* Q40_ISA_IO_B (unsigned long) ; 
 int /*<<< orphan*/  Q40_ISA_IO_W (unsigned long) ; 
 int /*<<< orphan*/  memset (struct ide_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void q40_ide_setup_ports(struct ide_hw *hw, unsigned long base, int irq)
{
	memset(hw, 0, sizeof(*hw));
	/* BIG FAT WARNING: 
	   assumption: only DATA port is ever used in 16 bit mode */
	hw->io_ports.data_addr = Q40_ISA_IO_W(base);
	hw->io_ports.error_addr = Q40_ISA_IO_B(base + 1);
	hw->io_ports.nsect_addr = Q40_ISA_IO_B(base + 2);
	hw->io_ports.lbal_addr = Q40_ISA_IO_B(base + 3);
	hw->io_ports.lbam_addr = Q40_ISA_IO_B(base + 4);
	hw->io_ports.lbah_addr = Q40_ISA_IO_B(base + 5);
	hw->io_ports.device_addr = Q40_ISA_IO_B(base + 6);
	hw->io_ports.status_addr = Q40_ISA_IO_B(base + 7);
	hw->io_ports.ctl_addr = Q40_ISA_IO_B(base + 0x206);

	hw->irq = irq;
}