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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct hfi1_devdata {int dummy; } ;
struct firmware_details {int firmware_len; int /*<<< orphan*/  signature; int /*<<< orphan*/ * firmware_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBUS_MASTER_BROADCAST ; 
 int /*<<< orphan*/  WRITE_SBUS_RECEIVER ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*) ; 
 int /*<<< orphan*/  load_security_variables (struct hfi1_devdata*,struct firmware_details*) ; 
 int run_rsa (struct hfi1_devdata*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbus_request (struct hfi1_devdata*,int /*<<< orphan*/  const,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int load_pcie_serdes_firmware(struct hfi1_devdata *dd,
				     struct firmware_details *fdet)
{
	int i;
	const u8 ra = SBUS_MASTER_BROADCAST; /* receiver address */

	dd_dev_info(dd, "Downloading PCIe firmware\n");

	/* step 1: load security variables */
	load_security_variables(dd, fdet);
	/* step 2: assert single step (halts the SBus Master spico) */
	sbus_request(dd, ra, 0x05, WRITE_SBUS_RECEIVER, 0x00000001);
	/* step 3: enable XDMEM access */
	sbus_request(dd, ra, 0x01, WRITE_SBUS_RECEIVER, 0x00000d40);
	/* step 4: load firmware into SBus Master XDMEM */
	/*
	 * NOTE: the dmem address, write_en, and wdata are all pre-packed,
	 * we only need to pick up the bytes and write them
	 */
	for (i = 0; i < fdet->firmware_len; i += 4) {
		sbus_request(dd, ra, 0x04, WRITE_SBUS_RECEIVER,
			     *(u32 *)&fdet->firmware_ptr[i]);
	}
	/* step 5: disable XDMEM access */
	sbus_request(dd, ra, 0x01, WRITE_SBUS_RECEIVER, 0x00000140);
	/* step 6: allow SBus Spico to run */
	sbus_request(dd, ra, 0x05, WRITE_SBUS_RECEIVER, 0x00000000);

	/*
	 * steps 7-11: run RSA, if it succeeds, firmware is available to
	 * be swapped
	 */
	return run_rsa(dd, "PCIe serdes", fdet->signature);
}