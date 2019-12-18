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
typedef  int u8 ;
struct wilco_ec_message {int val; int request_size; struct wilco_ec_message* request_data; int /*<<< orphan*/  type; int /*<<< orphan*/  sub_cmd; int /*<<< orphan*/  cmd; } ;
struct wilco_ec_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct boot_on_ac_request {int val; int request_size; struct boot_on_ac_request* request_data; int /*<<< orphan*/  type; int /*<<< orphan*/  sub_cmd; int /*<<< orphan*/  cmd; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  rq ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_KB_CMOS ; 
 int EINVAL ; 
 int /*<<< orphan*/  SUB_CMD_KB_CMOS_AUTO_ON ; 
 int /*<<< orphan*/  WILCO_EC_MSG_LEGACY ; 
 struct wilco_ec_device* dev_get_drvdata (struct device*) ; 
 int kstrtou8 (char const*,int,int*) ; 
 int /*<<< orphan*/  memset (struct wilco_ec_message*,int /*<<< orphan*/ ,int) ; 
 int wilco_ec_mailbox (struct wilco_ec_device*,struct wilco_ec_message*) ; 

__attribute__((used)) static ssize_t boot_on_ac_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct wilco_ec_device *ec = dev_get_drvdata(dev);
	struct boot_on_ac_request rq;
	struct wilco_ec_message msg;
	int ret;
	u8 val;

	ret = kstrtou8(buf, 10, &val);
	if (ret < 0)
		return ret;
	if (val > 1)
		return -EINVAL;

	memset(&rq, 0, sizeof(rq));
	rq.cmd = CMD_KB_CMOS;
	rq.sub_cmd = SUB_CMD_KB_CMOS_AUTO_ON;
	rq.val = val;

	memset(&msg, 0, sizeof(msg));
	msg.type = WILCO_EC_MSG_LEGACY;
	msg.request_data = &rq;
	msg.request_size = sizeof(rq);
	ret = wilco_ec_mailbox(ec, &msg);
	if (ret < 0)
		return ret;

	return count;
}