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
struct hfi1_devdata {size_t hfi1_id; } ;
struct firmware_details {int firmware_len; int /*<<< orphan*/  signature; int /*<<< orphan*/ * firmware_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_SBUS_RECEIVER ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*) ; 
 int /*<<< orphan*/ * fabric_serdes_broadcast ; 
 int /*<<< orphan*/  load_security_variables (struct hfi1_devdata*,struct firmware_details*) ; 
 int run_rsa (struct hfi1_devdata*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbus_request (struct hfi1_devdata*,int /*<<< orphan*/  const,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int load_fabric_serdes_firmware(struct hfi1_devdata *dd,
				       struct firmware_details *fdet)
{
	int i, err;
	const u8 ra = fabric_serdes_broadcast[dd->hfi1_id]; /* receiver addr */

	dd_dev_info(dd, "Downloading fabric firmware\n");

	/* step 1: load security variables */
	load_security_variables(dd, fdet);
	/* step 2: place SerDes in reset and disable SPICO */
	sbus_request(dd, ra, 0x07, WRITE_SBUS_RECEIVER, 0x00000011);
	/* wait 100 refclk cycles @ 156.25MHz => 640ns */
	udelay(1);
	/* step 3:  remove SerDes reset */
	sbus_request(dd, ra, 0x07, WRITE_SBUS_RECEIVER, 0x00000010);
	/* step 4: assert IMEM override */
	sbus_request(dd, ra, 0x00, WRITE_SBUS_RECEIVER, 0x40000000);
	/* step 5: download SerDes machine code */
	for (i = 0; i < fdet->firmware_len; i += 4) {
		sbus_request(dd, ra, 0x0a, WRITE_SBUS_RECEIVER,
			     *(u32 *)&fdet->firmware_ptr[i]);
	}
	/* step 6: IMEM override off */
	sbus_request(dd, ra, 0x00, WRITE_SBUS_RECEIVER, 0x00000000);
	/* step 7: turn ECC on */
	sbus_request(dd, ra, 0x0b, WRITE_SBUS_RECEIVER, 0x000c0000);

	/* steps 8-11: run the RSA engine */
	err = run_rsa(dd, "fabric serdes", fdet->signature);
	if (err)
		return err;

	/* step 12: turn SPICO enable on */
	sbus_request(dd, ra, 0x07, WRITE_SBUS_RECEIVER, 0x00000002);
	/* step 13: enable core hardware interrupts */
	sbus_request(dd, ra, 0x08, WRITE_SBUS_RECEIVER, 0x00000000);

	return 0;
}