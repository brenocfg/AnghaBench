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
struct i2c_msg {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; int /*<<< orphan*/  flags; } ;
struct i2c_command {int number_of_payloads; TYPE_1__* payloads; } ;
struct dc_link {struct amdgpu_dm_connector* priv; } ;
struct dc_context {int dummy; } ;
struct amdgpu_dm_connector {TYPE_2__* i2c; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; int /*<<< orphan*/  address; scalar_t__ write; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 struct i2c_msg* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct i2c_msg*) ; 

bool dm_helpers_submit_i2c(
		struct dc_context *ctx,
		const struct dc_link *link,
		struct i2c_command *cmd)
{
	struct amdgpu_dm_connector *aconnector = link->priv;
	struct i2c_msg *msgs;
	int i = 0;
	int num = cmd->number_of_payloads;
	bool result;

	if (!aconnector) {
		DRM_ERROR("Failed to found connector for link!");
		return false;
	}

	msgs = kcalloc(num, sizeof(struct i2c_msg), GFP_KERNEL);

	if (!msgs)
		return false;

	for (i = 0; i < num; i++) {
		msgs[i].flags = cmd->payloads[i].write ? 0 : I2C_M_RD;
		msgs[i].addr = cmd->payloads[i].address;
		msgs[i].len = cmd->payloads[i].length;
		msgs[i].buf = cmd->payloads[i].data;
	}

	result = i2c_transfer(&aconnector->i2c->base, msgs, num) == num;

	kfree(msgs);

	return result;
}