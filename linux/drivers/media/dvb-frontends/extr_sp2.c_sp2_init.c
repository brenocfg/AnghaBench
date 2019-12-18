#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {struct sp2* data; int /*<<< orphan*/  poll_slot_status; int /*<<< orphan*/  slot_ts_enable; int /*<<< orphan*/  slot_shutdown; int /*<<< orphan*/  slot_reset; int /*<<< orphan*/  write_cam_control; int /*<<< orphan*/  read_cam_control; int /*<<< orphan*/  write_attribute_mem; int /*<<< orphan*/  read_attribute_mem; int /*<<< orphan*/  owner; } ;
struct sp2 {TYPE_1__* client; TYPE_2__ ca; int /*<<< orphan*/  dvb_adap; scalar_t__ module_access_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int dvb_ca_en50221_init (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sp2_ci_poll_slot_status ; 
 int /*<<< orphan*/  sp2_ci_read_attribute_mem ; 
 int /*<<< orphan*/  sp2_ci_read_cam_control ; 
 int /*<<< orphan*/  sp2_ci_slot_reset ; 
 int /*<<< orphan*/  sp2_ci_slot_shutdown ; 
 int /*<<< orphan*/  sp2_ci_slot_ts_enable ; 
 int /*<<< orphan*/  sp2_ci_write_attribute_mem ; 
 int /*<<< orphan*/  sp2_ci_write_cam_control ; 
 int sp2_write_i2c (struct sp2*,int,int*,int) ; 

__attribute__((used)) static int sp2_init(struct sp2 *s)
{
	int ret = 0;
	u8 buf;
	u8 cimax_init[34] = {
		0x00, /* module A control*/
		0x00, /* auto select mask high A */
		0x00, /* auto select mask low A */
		0x00, /* auto select pattern high A */
		0x00, /* auto select pattern low A */
		0x44, /* memory access time A, 600 ns */
		0x00, /* invert input A */
		0x00, /* RFU */
		0x00, /* RFU */
		0x00, /* module B control*/
		0x00, /* auto select mask high B */
		0x00, /* auto select mask low B */
		0x00, /* auto select pattern high B */
		0x00, /* auto select pattern low B */
		0x44, /* memory access time B, 600 ns */
		0x00, /* invert input B */
		0x00, /* RFU */
		0x00, /* RFU */
		0x00, /* auto select mask high Ext */
		0x00, /* auto select mask low Ext */
		0x00, /* auto select pattern high Ext */
		0x00, /* auto select pattern low Ext */
		0x00, /* RFU */
		0x02, /* destination - module A */
		0x01, /* power control reg, VCC power on */
		0x00, /* RFU */
		0x00, /* int status read only */
		0x00, /* Interrupt Mask Register */
		0x05, /* EXTINT=active-high, INT=push-pull */
		0x00, /* USCG1 */
		0x04, /* ack active low */
		0x00, /* LOCK = 0 */
		0x22, /* unknown */
		0x00, /* synchronization? */
	};

	dev_dbg(&s->client->dev, "\n");

	s->ca.owner = THIS_MODULE;
	s->ca.read_attribute_mem = sp2_ci_read_attribute_mem;
	s->ca.write_attribute_mem = sp2_ci_write_attribute_mem;
	s->ca.read_cam_control = sp2_ci_read_cam_control;
	s->ca.write_cam_control = sp2_ci_write_cam_control;
	s->ca.slot_reset = sp2_ci_slot_reset;
	s->ca.slot_shutdown = sp2_ci_slot_shutdown;
	s->ca.slot_ts_enable = sp2_ci_slot_ts_enable;
	s->ca.poll_slot_status = sp2_ci_poll_slot_status;
	s->ca.data = s;
	s->module_access_type = 0;

	/* initialize all regs */
	ret = sp2_write_i2c(s, 0x00, &cimax_init[0], 34);
	if (ret)
		goto err;

	/* lock registers */
	buf = 1;
	ret = sp2_write_i2c(s, 0x1f, &buf, 1);
	if (ret)
		goto err;

	/* power on slots */
	ret = sp2_write_i2c(s, 0x18, &buf, 1);
	if (ret)
		goto err;

	ret = dvb_ca_en50221_init(s->dvb_adap, &s->ca, 0, 1);
	if (ret)
		goto err;

	return 0;

err:
	dev_dbg(&s->client->dev, "init failed=%d\n", ret);
	return ret;
}