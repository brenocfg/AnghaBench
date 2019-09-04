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
struct ec_response_get_version {int current_image; char* version_string_ro; char* version_string_rw; } ;
struct cros_ec_dev {int /*<<< orphan*/  ec_dev; scalar_t__ cmd_offset; } ;
struct cros_ec_command {int insize; scalar_t__ result; scalar_t__ data; scalar_t__ outsize; scalar_t__ command; scalar_t__ version; } ;

/* Variables and functions */
 int ARRAY_SIZE (char const* const*) ; 
 char* CROS_EC_DEV_VERSION ; 
 scalar_t__ EC_CMD_GET_VERSION ; 
 scalar_t__ EC_RES_SUCCESS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cros_ec_cmd_xfer (int /*<<< orphan*/ ,struct cros_ec_command*) ; 
 int /*<<< orphan*/  kfree (struct cros_ec_command*) ; 
 struct cros_ec_command* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,...) ; 

__attribute__((used)) static int ec_get_version(struct cros_ec_dev *ec, char *str, int maxlen)
{
	struct ec_response_get_version *resp;
	static const char * const current_image_name[] = {
		"unknown", "read-only", "read-write", "invalid",
	};
	struct cros_ec_command *msg;
	int ret;

	msg = kmalloc(sizeof(*msg) + sizeof(*resp), GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	msg->version = 0;
	msg->command = EC_CMD_GET_VERSION + ec->cmd_offset;
	msg->insize = sizeof(*resp);
	msg->outsize = 0;

	ret = cros_ec_cmd_xfer(ec->ec_dev, msg);
	if (ret < 0)
		goto exit;

	if (msg->result != EC_RES_SUCCESS) {
		snprintf(str, maxlen,
			 "%s\nUnknown EC version: EC returned %d\n",
			 CROS_EC_DEV_VERSION, msg->result);
		ret = -EINVAL;
		goto exit;
	}

	resp = (struct ec_response_get_version *)msg->data;
	if (resp->current_image >= ARRAY_SIZE(current_image_name))
		resp->current_image = 3; /* invalid */

	snprintf(str, maxlen, "%s\n%s\n%s\n%s\n", CROS_EC_DEV_VERSION,
		 resp->version_string_ro, resp->version_string_rw,
		 current_image_name[resp->current_image]);

	ret = 0;
exit:
	kfree(msg);
	return ret;
}