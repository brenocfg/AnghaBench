#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct i2c_payload {int dummy; } ;
struct i2c_msg {int flags; int /*<<< orphan*/  buf; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct i2c_command {int number_of_payloads; int speed; TYPE_4__* payloads; int /*<<< orphan*/  engine; } ;
struct i2c_adapter {int dummy; } ;
struct ddc_service {TYPE_3__* ddc_pin; TYPE_1__* ctx; } ;
struct amdgpu_i2c_adapter {struct ddc_service* ddc_service; } ;
struct TYPE_9__ {int write; int /*<<< orphan*/  data; int /*<<< orphan*/  length; int /*<<< orphan*/  address; } ;
struct TYPE_7__ {int /*<<< orphan*/  ddc_channel; } ;
struct TYPE_8__ {TYPE_2__ hw_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  dc; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_COMMAND_ENGINE_DEFAULT ; 
 int I2C_M_RD ; 
 scalar_t__ dc_submit_i2c (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i2c_command*) ; 
 struct amdgpu_i2c_adapter* i2c_get_adapdata (struct i2c_adapter*) ; 
 TYPE_4__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 

__attribute__((used)) static int amdgpu_dm_i2c_xfer(struct i2c_adapter *i2c_adap,
			      struct i2c_msg *msgs, int num)
{
	struct amdgpu_i2c_adapter *i2c = i2c_get_adapdata(i2c_adap);
	struct ddc_service *ddc_service = i2c->ddc_service;
	struct i2c_command cmd;
	int i;
	int result = -EIO;

	cmd.payloads = kcalloc(num, sizeof(struct i2c_payload), GFP_KERNEL);

	if (!cmd.payloads)
		return result;

	cmd.number_of_payloads = num;
	cmd.engine = I2C_COMMAND_ENGINE_DEFAULT;
	cmd.speed = 100;

	for (i = 0; i < num; i++) {
		cmd.payloads[i].write = !(msgs[i].flags & I2C_M_RD);
		cmd.payloads[i].address = msgs[i].addr;
		cmd.payloads[i].length = msgs[i].len;
		cmd.payloads[i].data = msgs[i].buf;
	}

	if (dc_submit_i2c(
			ddc_service->ctx->dc,
			ddc_service->ddc_pin->hw_info.ddc_channel,
			&cmd))
		result = num;

	kfree(cmd.payloads);
	return result;
}