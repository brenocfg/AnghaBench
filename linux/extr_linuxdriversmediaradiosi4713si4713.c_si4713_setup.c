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
struct v4l2_modulator {int /*<<< orphan*/  txsubchans; scalar_t__ index; } ;
struct v4l2_frequency {scalar_t__ frequency; scalar_t__ tuner; } ;
struct si4713_device {int /*<<< orphan*/  sd; scalar_t__ rds_enabled; scalar_t__ stereo; scalar_t__ frequency; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_FREQUENCY ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_MONO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_RDS ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_STEREO ; 
 int si4713_s_frequency (int /*<<< orphan*/ *,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  si4713_s_modulator (int /*<<< orphan*/ *,struct v4l2_modulator*) ; 
 scalar_t__ si4713_to_v4l2 (scalar_t__) ; 

__attribute__((used)) static int si4713_setup(struct si4713_device *sdev)
{
	struct v4l2_frequency f;
	struct v4l2_modulator vm;
	int rval;

	/* Device procedure needs to set frequency first */
	f.tuner = 0;
	f.frequency = sdev->frequency ? sdev->frequency : DEFAULT_FREQUENCY;
	f.frequency = si4713_to_v4l2(f.frequency);
	rval = si4713_s_frequency(&sdev->sd, &f);

	vm.index = 0;
	if (sdev->stereo)
		vm.txsubchans = V4L2_TUNER_SUB_STEREO;
	else
		vm.txsubchans = V4L2_TUNER_SUB_MONO;
	if (sdev->rds_enabled)
		vm.txsubchans |= V4L2_TUNER_SUB_RDS;
	si4713_s_modulator(&sdev->sd, &vm);

	return rval;
}