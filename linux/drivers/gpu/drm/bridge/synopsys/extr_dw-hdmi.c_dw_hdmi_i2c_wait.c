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
struct dw_hdmi_i2c {int stat; int /*<<< orphan*/  cmp; } ;
struct dw_hdmi {struct dw_hdmi_i2c* i2c; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int HDMI_IH_I2CM_STAT0_ERROR ; 
 int HZ ; 
 int /*<<< orphan*/  dw_hdmi_i2c_unwedge (struct dw_hdmi*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dw_hdmi_i2c_wait(struct dw_hdmi *hdmi)
{
	struct dw_hdmi_i2c *i2c = hdmi->i2c;
	int stat;

	stat = wait_for_completion_timeout(&i2c->cmp, HZ / 10);
	if (!stat) {
		/* If we can't unwedge, return timeout */
		if (!dw_hdmi_i2c_unwedge(hdmi))
			return -EAGAIN;

		/* We tried to unwedge; give it another chance */
		stat = wait_for_completion_timeout(&i2c->cmp, HZ / 10);
		if (!stat)
			return -EAGAIN;
	}

	/* Check for error condition on the bus */
	if (i2c->stat & HDMI_IH_I2CM_STAT0_ERROR)
		return -EIO;

	return 0;
}