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
struct amd_i2c_common {int dummy; } ;
struct amd_i2c_dev {struct amd_i2c_common common; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_mp2_bus_enable_set (struct amd_i2c_common*,int) ; 
 int i2c_amd_check_cmd_completion (struct amd_i2c_dev*) ; 
 int /*<<< orphan*/  i2c_amd_start_cmd (struct amd_i2c_dev*) ; 

__attribute__((used)) static int i2c_amd_enable_set(struct amd_i2c_dev *i2c_dev, bool enable)
{
	struct amd_i2c_common *i2c_common = &i2c_dev->common;

	i2c_amd_start_cmd(i2c_dev);
	amd_mp2_bus_enable_set(i2c_common, enable);

	return i2c_amd_check_cmd_completion(i2c_dev);
}