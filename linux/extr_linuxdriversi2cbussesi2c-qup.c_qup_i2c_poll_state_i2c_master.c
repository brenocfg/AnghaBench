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
struct qup_i2c_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUP_I2C_MAST_GEN ; 
 int qup_i2c_poll_state_mask (struct qup_i2c_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qup_i2c_poll_state_i2c_master(struct qup_i2c_dev *qup)
{
	return qup_i2c_poll_state_mask(qup, QUP_I2C_MAST_GEN, QUP_I2C_MAST_GEN);
}