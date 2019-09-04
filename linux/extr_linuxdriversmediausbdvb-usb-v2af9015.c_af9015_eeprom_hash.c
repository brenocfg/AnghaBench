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
typedef  int /*<<< orphan*/  u32 ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct req_t {int member_4; int member_5; int addr; int /*<<< orphan*/ * data; int /*<<< orphan*/ * member_6; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dvb_usb_device {struct usb_interface* intf; } ;
struct af9015_state {int eeprom_sum; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int AF9015_EEPROM_SIZE ; 
 int /*<<< orphan*/  AF9015_I2C_EEPROM ; 
 int GOLDEN_RATIO_PRIME_32 ; 
 int /*<<< orphan*/  READ_I2C ; 
 int af9015_ctrl_msg (struct dvb_usb_device*,struct req_t*) ; 
 struct af9015_state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int af9015_eeprom_hash(struct dvb_usb_device *d)
{
	struct af9015_state *state = d_to_priv(d);
	struct usb_interface *intf = d->intf;
	int ret, i;
	u8 buf[AF9015_EEPROM_SIZE];
	struct req_t req = {READ_I2C, AF9015_I2C_EEPROM, 0, 0, 1, 1, NULL};

	/* read eeprom */
	for (i = 0; i < AF9015_EEPROM_SIZE; i++) {
		req.addr = i;
		req.data = &buf[i];
		ret = af9015_ctrl_msg(d, &req);
		if (ret < 0)
			goto err;
	}

	/* calculate checksum */
	for (i = 0; i < AF9015_EEPROM_SIZE / sizeof(u32); i++) {
		state->eeprom_sum *= GOLDEN_RATIO_PRIME_32;
		state->eeprom_sum += le32_to_cpu(((__le32 *)buf)[i]);
	}

	for (i = 0; i < AF9015_EEPROM_SIZE; i += 16)
		dev_dbg(&intf->dev, "%*ph\n", 16, buf + i);

	dev_dbg(&intf->dev, "eeprom sum %.8x\n", state->eeprom_sum);
	return 0;
err:
	dev_dbg(&intf->dev, "failed %d\n", ret);
	return ret;
}