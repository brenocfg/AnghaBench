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
struct cros_ec_dev {scalar_t__ cmd_offset; } ;
struct cros_ec_command {unsigned int version; unsigned int outsize; unsigned int insize; void* data; scalar_t__ command; } ;
struct charger_data {int /*<<< orphan*/  ec_device; struct cros_ec_dev* ec_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cros_ec_cmd_xfer_status (int /*<<< orphan*/ ,struct cros_ec_command*) ; 
 int /*<<< orphan*/  kfree (struct cros_ec_command*) ; 
 struct cros_ec_command* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ max (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 

__attribute__((used)) static int cros_usbpd_charger_ec_command(struct charger_data *charger,
					 unsigned int version,
					 unsigned int command,
					 void *outdata,
					 unsigned int outsize,
					 void *indata,
					 unsigned int insize)
{
	struct cros_ec_dev *ec_dev = charger->ec_dev;
	struct cros_ec_command *msg;
	int ret;

	msg = kzalloc(sizeof(*msg) + max(outsize, insize), GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	msg->version = version;
	msg->command = ec_dev->cmd_offset + command;
	msg->outsize = outsize;
	msg->insize = insize;

	if (outsize)
		memcpy(msg->data, outdata, outsize);

	ret = cros_ec_cmd_xfer_status(charger->ec_device, msg);
	if (ret >= 0 && insize)
		memcpy(indata, msg->data, insize);

	kfree(msg);
	return ret;
}