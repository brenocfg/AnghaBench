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
struct ec_response_lightbar {int dummy; } ;
struct ec_params_lightbar {int dummy; } ;
struct cros_ec_dev {scalar_t__ cmd_offset; } ;
struct cros_ec_command {int outsize; int insize; scalar_t__ command; scalar_t__ version; } ;

/* Variables and functions */
 scalar_t__ EC_CMD_LIGHTBAR_CMD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct cros_ec_command* kmalloc (int,int /*<<< orphan*/ ) ; 
 int max (int,int) ; 

__attribute__((used)) static struct cros_ec_command *alloc_lightbar_cmd_msg(struct cros_ec_dev *ec)
{
	struct cros_ec_command *msg;
	int len;

	len = max(sizeof(struct ec_params_lightbar),
		  sizeof(struct ec_response_lightbar));

	msg = kmalloc(sizeof(*msg) + len, GFP_KERNEL);
	if (!msg)
		return NULL;

	msg->version = 0;
	msg->command = EC_CMD_LIGHTBAR_CMD + ec->cmd_offset;
	msg->outsize = sizeof(struct ec_params_lightbar);
	msg->insize = sizeof(struct ec_response_lightbar);

	return msg;
}