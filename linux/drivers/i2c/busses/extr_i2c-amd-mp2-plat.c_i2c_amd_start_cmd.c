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
struct amd_i2c_common {int cmd_success; } ;
struct amd_i2c_dev {int /*<<< orphan*/  cmd_complete; struct amd_i2c_common common; } ;

/* Variables and functions */
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i2c_amd_start_cmd(struct amd_i2c_dev *i2c_dev)
{
	struct amd_i2c_common *i2c_common = &i2c_dev->common;

	reinit_completion(&i2c_dev->cmd_complete);
	i2c_common->cmd_success = false;
}