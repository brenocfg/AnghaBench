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
typedef  void* u16 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_modulator {scalar_t__ index; int txsubchans; } ;
struct si4713_device {void* rds_enabled; void* stereo; scalar_t__ power_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  SI4713_TX_COMPONENT_ENABLE ; 
 int V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_RDS ; 
 int V4L2_TUNER_SUB_STEREO ; 
 int /*<<< orphan*/  set_bits (int /*<<< orphan*/ ,void*,int,int) ; 
 int si4713_read_property (struct si4713_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int si4713_write_property (struct si4713_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct si4713_device* to_si4713_device (struct v4l2_subdev*) ; 

__attribute__((used)) static int si4713_s_modulator(struct v4l2_subdev *sd, const struct v4l2_modulator *vm)
{
	struct si4713_device *sdev = to_si4713_device(sd);
	int rval = 0;
	u16 stereo, rds;
	u32 p;

	if (!sdev)
		return -ENODEV;

	if (vm->index > 0)
		return -EINVAL;

	/* Set audio mode: mono or stereo */
	if (vm->txsubchans & V4L2_TUNER_SUB_STEREO)
		stereo = 1;
	else if (vm->txsubchans & V4L2_TUNER_SUB_MONO)
		stereo = 0;
	else
		return -EINVAL;

	rds = !!(vm->txsubchans & V4L2_TUNER_SUB_RDS);

	if (sdev->power_state) {
		rval = si4713_read_property(sdev,
						SI4713_TX_COMPONENT_ENABLE, &p);
		if (rval < 0)
			return rval;

		p = set_bits(p, stereo, 1, 1 << 1);
		p = set_bits(p, rds, 2, 1 << 2);

		rval = si4713_write_property(sdev,
						SI4713_TX_COMPONENT_ENABLE, p);
		if (rval < 0)
			return rval;
	}

	sdev->stereo = stereo;
	sdev->rds_enabled = rds;

	return rval;
}