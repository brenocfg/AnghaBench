#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct i2c_msg {scalar_t__ flags; } ;
struct i2c_algo_pch_data {int pch_i2c_xfer_in_progress; scalar_t__ pch_buff_mode_en; TYPE_1__* p_adapter_info; } ;
struct i2c_adapter {struct i2c_algo_pch_data* algo_data; } ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {scalar_t__ pch_i2c_suspended; } ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 scalar_t__ I2C_M_RD ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pch_dbg (struct i2c_algo_pch_data*,char*,scalar_t__) ; 
 scalar_t__ pch_i2c_readbytes (struct i2c_adapter*,struct i2c_msg*,int,int) ; 
 scalar_t__ pch_i2c_writebytes (struct i2c_adapter*,struct i2c_msg*,int,int) ; 
 int /*<<< orphan*/  pch_mutex ; 

__attribute__((used)) static s32 pch_i2c_xfer(struct i2c_adapter *i2c_adap,
			struct i2c_msg *msgs, s32 num)
{
	struct i2c_msg *pmsg;
	u32 i = 0;
	u32 status;
	s32 ret;

	struct i2c_algo_pch_data *adap = i2c_adap->algo_data;

	ret = mutex_lock_interruptible(&pch_mutex);
	if (ret)
		return ret;

	if (adap->p_adapter_info->pch_i2c_suspended) {
		mutex_unlock(&pch_mutex);
		return -EBUSY;
	}

	pch_dbg(adap, "adap->p_adapter_info->pch_i2c_suspended is %d\n",
		adap->p_adapter_info->pch_i2c_suspended);
	/* transfer not completed */
	adap->pch_i2c_xfer_in_progress = true;

	for (i = 0; i < num && ret >= 0; i++) {
		pmsg = &msgs[i];
		pmsg->flags |= adap->pch_buff_mode_en;
		status = pmsg->flags;
		pch_dbg(adap,
			"After invoking I2C_MODE_SEL :flag= 0x%x\n", status);

		if ((status & (I2C_M_RD)) != false) {
			ret = pch_i2c_readbytes(i2c_adap, pmsg, (i + 1 == num),
						(i == 0));
		} else {
			ret = pch_i2c_writebytes(i2c_adap, pmsg, (i + 1 == num),
						 (i == 0));
		}
	}

	adap->pch_i2c_xfer_in_progress = false;	/* transfer completed */

	mutex_unlock(&pch_mutex);

	return (ret < 0) ? ret : num;
}