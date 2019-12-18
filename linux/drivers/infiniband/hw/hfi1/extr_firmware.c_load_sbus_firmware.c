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

__attribute__((used)) static int load_sbus_firmware(struct hfi1_devdata *dd,
			      struct firmware_details *fdet)
{
	int i, err;
	const u8 ra = SBUS_MASTER_BROADCAST; /* receiver address */

	dd_dev_info(dd, "Downloading SBus firmware\n");

	/* step 1: load security variables */
	load_security_variables(dd, fdet);
	/* step 2: place SPICO into reset and enable off */
	sbus_request(dd, ra, 0x01, WRITE_SBUS_RECEIVER, 0x000000c0);
	/* step 3: remove reset, enable off, IMEM_CNTRL_EN on */
	sbus_request(dd, ra, 0x01, WRITE_SBUS_RECEIVER, 0x00000240);
	/* step 4: set starting IMEM address for burst download */
	sbus_request(dd, ra, 0x03, WRITE_SBUS_RECEIVER, 0x80000000);
	/* step 5: download the SBus Master machine code */
	for (i = 0; i < fdet->firmware_len; i += 4) {
		sbus_request(dd, ra, 0x14, WRITE_SBUS_RECEIVER,
			     *(u32 *)&fdet->firmware_ptr[i]);
	}
	/* step 6: set IMEM_CNTL_EN off */
	sbus_request(dd, ra, 0x01, WRITE_SBUS_RECEIVER, 0x00000040);
	/* step 7: turn ECC on */
	sbus_request(dd, ra, 0x16, WRITE_SBUS_RECEIVER, 0x000c0000);

	/* steps 8-11: run the RSA engine */
	err = run_rsa(dd, "SBus", fdet->signature);
	if (err)
		return err;

	/* step 12: set SPICO_ENABLE on */
	sbus_request(dd, ra, 0x01, WRITE_SBUS_RECEIVER, 0x00000140);

	return 0;
}