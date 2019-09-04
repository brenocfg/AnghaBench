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
struct vsp1_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  VI6_SRESET ; 
 int /*<<< orphan*/  VI6_SRESET_SRTS (unsigned int) ; 
 int /*<<< orphan*/  VI6_STATUS ; 
 int VI6_STATUS_SYS_ACT (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int vsp1_read (struct vsp1_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_write (struct vsp1_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vsp1_reset_wpf(struct vsp1_device *vsp1, unsigned int index)
{
	unsigned int timeout;
	u32 status;

	status = vsp1_read(vsp1, VI6_STATUS);
	if (!(status & VI6_STATUS_SYS_ACT(index)))
		return 0;

	vsp1_write(vsp1, VI6_SRESET, VI6_SRESET_SRTS(index));
	for (timeout = 10; timeout > 0; --timeout) {
		status = vsp1_read(vsp1, VI6_STATUS);
		if (!(status & VI6_STATUS_SYS_ACT(index)))
			break;

		usleep_range(1000, 2000);
	}

	if (!timeout) {
		dev_err(vsp1->dev, "failed to reset wpf.%u\n", index);
		return -ETIMEDOUT;
	}

	return 0;
}