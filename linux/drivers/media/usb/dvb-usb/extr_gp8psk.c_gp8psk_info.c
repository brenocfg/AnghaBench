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
typedef  scalar_t__ u8 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GP8PSK_FW_VERS (scalar_t__*) ; 
 int /*<<< orphan*/  gp8psk_get_fpga_version (struct dvb_usb_device*,scalar_t__*) ; 
 int /*<<< orphan*/  gp8psk_get_fw_version (struct dvb_usb_device*,scalar_t__*) ; 
 int /*<<< orphan*/  info (char*,...) ; 

__attribute__((used)) static void gp8psk_info(struct dvb_usb_device *d)
{
	u8 fpga_vers, fw_vers[6];

	if (!gp8psk_get_fw_version(d, fw_vers))
		info("FW Version = %i.%02i.%i (0x%x)  Build %4i/%02i/%02i",
		fw_vers[2], fw_vers[1], fw_vers[0], GP8PSK_FW_VERS(fw_vers),
		2000 + fw_vers[5], fw_vers[4], fw_vers[3]);
	else
		info("failed to get FW version");

	if (!gp8psk_get_fpga_version(d, &fpga_vers))
		info("FPGA Version = %i", fpga_vers);
	else
		info("failed to get FPGA version");
}