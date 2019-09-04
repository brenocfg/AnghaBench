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
struct wmt_i2c_dev {int cmd_status; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int ISR_NACK_ADDR ; 
 int ISR_SCL_TIMEOUT ; 

__attribute__((used)) static int wmt_check_status(struct wmt_i2c_dev *i2c_dev)
{
	int ret = 0;

	if (i2c_dev->cmd_status & ISR_NACK_ADDR)
		ret = -EIO;

	if (i2c_dev->cmd_status & ISR_SCL_TIMEOUT)
		ret = -ETIMEDOUT;

	return ret;
}