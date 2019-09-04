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
typedef  int /*<<< orphan*/  u32 ;
struct altr_i2c_dev {int msg_len; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ ALTR_I2C_TFR_CMD ; 
 int /*<<< orphan*/  ALTR_I2C_TFR_CMD_STO ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void altr_i2c_transfer(struct altr_i2c_dev *idev, u32 data)
{
	/* On the last byte to be transmitted, send STOP */
	if (idev->msg_len == 1)
		data |= ALTR_I2C_TFR_CMD_STO;
	if (idev->msg_len > 0)
		writel(data, idev->base + ALTR_I2C_TFR_CMD);
}