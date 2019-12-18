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
struct dvb_usb_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPERA_READ_MSG ; 
 int /*<<< orphan*/  OPERA_WRITE_MSG ; 
 int /*<<< orphan*/  READ_MAC_ADDR ; 
 int /*<<< orphan*/  opera1_xilinx_rw (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opera1_read_mac_address(struct dvb_usb_device *d, u8 mac[6])
{
	u8 command[] = { READ_MAC_ADDR };
	opera1_xilinx_rw(d->udev, 0xb1, 0xa0, command, 1, OPERA_WRITE_MSG);
	opera1_xilinx_rw(d->udev, 0xb1, 0xa1, mac, 6, OPERA_READ_MSG);
	return 0;
}