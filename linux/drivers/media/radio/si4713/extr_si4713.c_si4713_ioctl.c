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
typedef  int /*<<< orphan*/  u16 ;
struct v4l2_subdev {int dummy; } ;
struct si4713_rnl {int /*<<< orphan*/  rnl; int /*<<< orphan*/  frequency; } ;
struct si4713_device {int /*<<< orphan*/  tune_rnl; int /*<<< orphan*/  power_state; } ;

/* Variables and functions */
 long EINVAL ; 
 int ENOIOCTLCMD ; 
#define  SI4713_IOC_MEASURE_RNL 128 
 int si4713_tx_tune_measure (struct si4713_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int si4713_update_tune_status (struct si4713_device*) ; 
 struct si4713_device* to_si4713_device (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_to_si4713 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long si4713_ioctl(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
	struct si4713_device *sdev = to_si4713_device(sd);
	struct si4713_rnl *rnl = arg;
	u16 frequency;
	int rval = 0;

	if (!arg)
		return -EINVAL;

	switch (cmd) {
	case SI4713_IOC_MEASURE_RNL:
		frequency = v4l2_to_si4713(rnl->frequency);

		if (sdev->power_state) {
			/* Set desired measurement frequency */
			rval = si4713_tx_tune_measure(sdev, frequency, 0);
			if (rval < 0)
				return rval;
			/* get results from tune status */
			rval = si4713_update_tune_status(sdev);
			if (rval < 0)
				return rval;
		}
		rnl->rnl = sdev->tune_rnl;
		break;

	default:
		/* nothing */
		rval = -ENOIOCTLCMD;
	}

	return rval;
}