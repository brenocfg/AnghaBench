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
struct cros_ec_dev {unsigned int* features; int /*<<< orphan*/  dev; int /*<<< orphan*/  ec_dev; scalar_t__ cmd_offset; } ;
struct cros_ec_command {scalar_t__ result; int /*<<< orphan*/  data; scalar_t__ outsize; int /*<<< orphan*/  insize; scalar_t__ command; scalar_t__ version; } ;

/* Variables and functions */
 scalar_t__ EC_CMD_GET_FEATURES ; 
 int EC_FEATURE_MASK_0 (int) ; 
 scalar_t__ EC_RES_SUCCESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cros_ec_cmd_xfer (int /*<<< orphan*/ ,struct cros_ec_command*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct cros_ec_command*) ; 
 struct cros_ec_command* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cros_ec_check_features(struct cros_ec_dev *ec, int feature)
{
	struct cros_ec_command *msg;
	int ret;

	if (ec->features[0] == -1U && ec->features[1] == -1U) {
		/* features bitmap not read yet */

		msg = kmalloc(sizeof(*msg) + sizeof(ec->features), GFP_KERNEL);
		if (!msg)
			return -ENOMEM;

		msg->version = 0;
		msg->command = EC_CMD_GET_FEATURES + ec->cmd_offset;
		msg->insize = sizeof(ec->features);
		msg->outsize = 0;

		ret = cros_ec_cmd_xfer(ec->ec_dev, msg);
		if (ret < 0 || msg->result != EC_RES_SUCCESS) {
			dev_warn(ec->dev, "cannot get EC features: %d/%d\n",
				 ret, msg->result);
			memset(ec->features, 0, sizeof(ec->features));
		} else {
			memcpy(ec->features, msg->data, sizeof(ec->features));
		}

		dev_dbg(ec->dev, "EC features %08x %08x\n",
			ec->features[0], ec->features[1]);

		kfree(msg);
	}

	return ec->features[feature / 32] & EC_FEATURE_MASK_0(feature);
}