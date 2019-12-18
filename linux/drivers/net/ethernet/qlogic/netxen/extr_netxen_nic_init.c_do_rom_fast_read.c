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
struct netxen_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NETXEN_ROMUSB_ROM_ABYTE_CNT ; 
 int /*<<< orphan*/  NETXEN_ROMUSB_ROM_ADDRESS ; 
 int /*<<< orphan*/  NETXEN_ROMUSB_ROM_DUMMY_BYTE_CNT ; 
 int /*<<< orphan*/  NETXEN_ROMUSB_ROM_INSTR_OPCODE ; 
 int /*<<< orphan*/  NETXEN_ROMUSB_ROM_RDATA ; 
 int NXRD32 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netxen_wait_rom_done (struct netxen_adapter*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int do_rom_fast_read(struct netxen_adapter *adapter,
			    int addr, int *valp)
{
	NXWR32(adapter, NETXEN_ROMUSB_ROM_ADDRESS, addr);
	NXWR32(adapter, NETXEN_ROMUSB_ROM_DUMMY_BYTE_CNT, 0);
	NXWR32(adapter, NETXEN_ROMUSB_ROM_ABYTE_CNT, 3);
	NXWR32(adapter, NETXEN_ROMUSB_ROM_INSTR_OPCODE, 0xb);
	if (netxen_wait_rom_done(adapter)) {
		printk("Error waiting for rom done\n");
		return -EIO;
	}
	/* reset abyte_cnt and dummy_byte_cnt */
	NXWR32(adapter, NETXEN_ROMUSB_ROM_ABYTE_CNT, 0);
	udelay(10);
	NXWR32(adapter, NETXEN_ROMUSB_ROM_DUMMY_BYTE_CNT, 0);

	*valp = NXRD32(adapter, NETXEN_ROMUSB_ROM_RDATA);
	return 0;
}