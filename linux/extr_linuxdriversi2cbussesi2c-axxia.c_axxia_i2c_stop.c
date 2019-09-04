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
typedef  int u32 ;
struct axxia_i2c_dev {int /*<<< orphan*/  dev; scalar_t__ base; int /*<<< orphan*/  msg_complete; } ;

/* Variables and functions */
 int CMD_BUSY ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I2C_STOP_TIMEOUT ; 
 scalar_t__ MST_COMMAND ; 
 int MST_STATUS_ERR ; 
 int MST_STATUS_SCC ; 
 int MST_STATUS_TSS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  i2c_int_disable (struct axxia_i2c_dev*,int) ; 
 int /*<<< orphan*/  i2c_int_enable (struct axxia_i2c_dev*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int axxia_i2c_stop(struct axxia_i2c_dev *idev)
{
	u32 int_mask = MST_STATUS_ERR | MST_STATUS_SCC | MST_STATUS_TSS;
	unsigned long time_left;

	reinit_completion(&idev->msg_complete);

	/* Issue stop */
	writel(0xb, idev->base + MST_COMMAND);
	i2c_int_enable(idev, int_mask);
	time_left = wait_for_completion_timeout(&idev->msg_complete,
					      I2C_STOP_TIMEOUT);
	i2c_int_disable(idev, int_mask);
	if (time_left == 0)
		return -ETIMEDOUT;

	if (readl(idev->base + MST_COMMAND) & CMD_BUSY)
		dev_warn(idev->dev, "busy after stop\n");

	return 0;
}