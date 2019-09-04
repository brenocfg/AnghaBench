#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct i2c_msg {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct i2c_adapter {TYPE_2__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct TYPE_9__ {TYPE_1__ dev; } ;
struct dibx000_i2c_master {int i2c_addr; int base_reg; int /*<<< orphan*/  i2c_buffer_lock; TYPE_3__* msg; int /*<<< orphan*/  i2c_write_buffer; TYPE_5__ master_i2c_adap_gpio67; struct i2c_adapter* i2c_adap; TYPE_5__ master_i2c_adap_gpio34; TYPE_5__ master_i2c_adap_gpio12; TYPE_5__ gated_tuner_i2c_adap; scalar_t__ device_rev; } ;
struct TYPE_8__ {int addr; int len; int /*<<< orphan*/  buf; scalar_t__ flags; } ;

/* Variables and functions */
 scalar_t__ DIB7000P ; 
 scalar_t__ DIB8000 ; 
 int EINVAL ; 
 int /*<<< orphan*/  dibx000_i2c_gate_ctrl (struct dibx000_i2c_master*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dibx000_i2c_gated_gpio67_algo ; 
 int /*<<< orphan*/  dibx000_i2c_gated_tuner_algo ; 
 int /*<<< orphan*/  dibx000_i2c_master_gpio12_xfer_algo ; 
 int /*<<< orphan*/  dibx000_i2c_master_gpio34_xfer_algo ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 scalar_t__ i2c_adapter_init (TYPE_5__*,int /*<<< orphan*/ *,char*,struct dibx000_i2c_master*) ; 
 int i2c_transfer (struct i2c_adapter*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int dibx000_init_i2c_master(struct dibx000_i2c_master *mst, u16 device_rev,
				struct i2c_adapter *i2c_adap, u8 i2c_addr)
{
	int ret;

	mutex_init(&mst->i2c_buffer_lock);
	if (mutex_lock_interruptible(&mst->i2c_buffer_lock) < 0) {
		dprintk("could not acquire lock\n");
		return -EINVAL;
	}
	memset(mst->msg, 0, sizeof(struct i2c_msg));
	mst->msg[0].addr = i2c_addr >> 1;
	mst->msg[0].flags = 0;
	mst->msg[0].buf = mst->i2c_write_buffer;
	mst->msg[0].len = 4;

	mst->device_rev = device_rev;
	mst->i2c_adap = i2c_adap;
	mst->i2c_addr = i2c_addr >> 1;

	if (device_rev == DIB7000P || device_rev == DIB8000)
		mst->base_reg = 1024;
	else
		mst->base_reg = 768;

	mst->gated_tuner_i2c_adap.dev.parent = mst->i2c_adap->dev.parent;
	if (i2c_adapter_init
			(&mst->gated_tuner_i2c_adap, &dibx000_i2c_gated_tuner_algo,
			 "DiBX000 tuner I2C bus", mst) != 0)
		pr_err("could not initialize the tuner i2c_adapter\n");

	mst->master_i2c_adap_gpio12.dev.parent = mst->i2c_adap->dev.parent;
	if (i2c_adapter_init
			(&mst->master_i2c_adap_gpio12, &dibx000_i2c_master_gpio12_xfer_algo,
			 "DiBX000 master GPIO12 I2C bus", mst) != 0)
		pr_err("could not initialize the master i2c_adapter\n");

	mst->master_i2c_adap_gpio34.dev.parent = mst->i2c_adap->dev.parent;
	if (i2c_adapter_init
			(&mst->master_i2c_adap_gpio34, &dibx000_i2c_master_gpio34_xfer_algo,
			 "DiBX000 master GPIO34 I2C bus", mst) != 0)
		pr_err("could not initialize the master i2c_adapter\n");

	mst->master_i2c_adap_gpio67.dev.parent = mst->i2c_adap->dev.parent;
	if (i2c_adapter_init
			(&mst->master_i2c_adap_gpio67, &dibx000_i2c_gated_gpio67_algo,
			 "DiBX000 master GPIO67 I2C bus", mst) != 0)
		pr_err("could not initialize the master i2c_adapter\n");

	/* initialize the i2c-master by closing the gate */
	dibx000_i2c_gate_ctrl(mst, mst->i2c_write_buffer, 0, 0);

	ret = (i2c_transfer(i2c_adap, mst->msg, 1) == 1);
	mutex_unlock(&mst->i2c_buffer_lock);

	return ret;
}