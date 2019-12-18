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
typedef  int u64 ;
struct kp2000_device {int card_id; int build_version; int build_datestamp; int build_timestamp; int core_table_length; int core_table_offset; int core_table_rev; int hardware_revision; int ddna; TYPE_1__* pdev; int /*<<< orphan*/  ssid; scalar_t__ sysinfo_regs_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EILSEQ ; 
 int KP2000_MAGIC_VALUE ; 
 scalar_t__ REG_CARD_ID_AND_BUILD ; 
 scalar_t__ REG_CORE_TABLE_OFFSET ; 
 scalar_t__ REG_DATE_AND_TIME_STAMPS ; 
 scalar_t__ REG_FPGA_DDNA ; 
 scalar_t__ REG_FPGA_HW_ID ; 
 scalar_t__ REG_MAGIC_NUMBER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int) ; 
 int readq (scalar_t__) ; 
 int /*<<< orphan*/  wait_and_read_ssid (struct kp2000_device*) ; 

__attribute__((used)) static int  read_system_regs(struct kp2000_device *pcard)
{
	u64 read_val;

	read_val = readq(pcard->sysinfo_regs_base + REG_MAGIC_NUMBER);
	if (read_val != KP2000_MAGIC_VALUE) {
		dev_err(&pcard->pdev->dev,
			"Invalid magic!  Got: 0x%016llx  Want: 0x%016llx\n",
			read_val, KP2000_MAGIC_VALUE);
		return -EILSEQ;
	}

	read_val = readq(pcard->sysinfo_regs_base + REG_CARD_ID_AND_BUILD);
	pcard->card_id = (read_val & 0xFFFFFFFF00000000UL) >> 32;
	pcard->build_version = (read_val & 0x00000000FFFFFFFFUL) >> 0;

	read_val = readq(pcard->sysinfo_regs_base + REG_DATE_AND_TIME_STAMPS);
	pcard->build_datestamp = (read_val & 0xFFFFFFFF00000000UL) >> 32;
	pcard->build_timestamp = (read_val & 0x00000000FFFFFFFFUL) >> 0;

	read_val = readq(pcard->sysinfo_regs_base + REG_CORE_TABLE_OFFSET);
	pcard->core_table_length = (read_val & 0xFFFFFFFF00000000UL) >> 32;
	pcard->core_table_offset = (read_val & 0x00000000FFFFFFFFUL) >> 0;

	wait_and_read_ssid(pcard);

	read_val = readq(pcard->sysinfo_regs_base + REG_FPGA_HW_ID);
	pcard->core_table_rev    = (read_val & 0x0000000000000F00) >> 8;
	pcard->hardware_revision = (read_val & 0x000000000000001F);

	read_val = readq(pcard->sysinfo_regs_base + REG_FPGA_DDNA);
	pcard->ddna = read_val;

	dev_info(&pcard->pdev->dev,
		 "system_regs: %08x %08x %08x %08x  %02x  %d %d  %016llx  %016llx\n",
		 pcard->card_id,
		 pcard->build_version,
		 pcard->build_datestamp,
		 pcard->build_timestamp,
		 pcard->hardware_revision,
		 pcard->core_table_rev,
		 pcard->core_table_length,
		 pcard->ssid,
		 pcard->ddna);

	if (pcard->core_table_rev > 1) {
		dev_err(&pcard->pdev->dev,
			"core table entry revision is higher than we can deal with, cannot continue with this card!\n");
		return 1;
	}

	return 0;
}