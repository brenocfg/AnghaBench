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
struct i2c_device_addr {int dummy; } ;
struct TYPE_2__ {int audio_is_active; } ;
struct drxj_data {TYPE_1__ aud_data; } ;
struct drx_demod_instance {scalar_t__ my_ext_attr; scalar_t__ my_i2c_dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_COMM_EXEC_STOP ; 
 int /*<<< orphan*/  AUD_COMM_EXEC__A ; 
 int drxj_dap_write_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int power_down_aud(struct drx_demod_instance *demod)
{
	struct i2c_device_addr *dev_addr = NULL;
	struct drxj_data *ext_attr = NULL;
	int rc;

	dev_addr = (struct i2c_device_addr *)demod->my_i2c_dev_addr;
	ext_attr = (struct drxj_data *) demod->my_ext_attr;

	rc = drxj_dap_write_reg16(dev_addr, AUD_COMM_EXEC__A, AUD_COMM_EXEC_STOP, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	ext_attr->aud_data.audio_is_active = false;

	return 0;
rw_error:
	return rc;
}