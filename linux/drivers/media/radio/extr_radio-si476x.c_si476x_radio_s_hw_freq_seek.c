#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct v4l2_hw_freq_seek {scalar_t__ rangelow; scalar_t__ rangehigh; scalar_t__ tuner; scalar_t__ type; scalar_t__ spacing; int /*<<< orphan*/  wrap_around; int /*<<< orphan*/  seek_upward; } ;
struct si476x_radio {TYPE_2__* core; TYPE_1__* ops; } ;
struct file {int f_flags; } ;
typedef  enum si476x_func { ____Placeholder_si476x_func } si476x_func ;
struct TYPE_9__ {int /*<<< orphan*/  regmap; } ;
struct TYPE_8__ {int (* seek_start ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SI476X_BAND_AM ; 
 int /*<<< orphan*/  SI476X_BAND_FM ; 
 int SI476X_FUNC_AM_RECEIVER ; 
 int SI476X_FUNC_FM_RECEIVER ; 
 int /*<<< orphan*/  SI476X_PROP_SEEK_BAND_BOTTOM ; 
 int /*<<< orphan*/  SI476X_PROP_SEEK_BAND_TOP ; 
 int /*<<< orphan*/  SI476X_PROP_SEEK_FREQUENCY_SPACING ; 
 scalar_t__ V4L2_TUNER_RADIO ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ si476x_core_has_am (TYPE_2__*) ; 
 int /*<<< orphan*/  si476x_core_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  si476x_core_unlock (TYPE_2__*) ; 
 int si476x_radio_change_func (struct si476x_radio*,int) ; 
 scalar_t__ si476x_radio_range_is_inside_of_the_band (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ si476x_to_v4l2 (TYPE_2__*,scalar_t__) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_to_si476x (TYPE_2__*,scalar_t__) ; 
 struct si476x_radio* video_drvdata (struct file*) ; 

__attribute__((used)) static int si476x_radio_s_hw_freq_seek(struct file *file, void *priv,
				       const struct v4l2_hw_freq_seek *seek)
{
	int err;
	enum si476x_func func;
	u32 rangelow = seek->rangelow, rangehigh = seek->rangehigh;
	struct si476x_radio *radio = video_drvdata(file);

	if (file->f_flags & O_NONBLOCK)
		return -EAGAIN;

	if (seek->tuner != 0 ||
	    seek->type  != V4L2_TUNER_RADIO)
		return -EINVAL;

	si476x_core_lock(radio->core);

	if (!rangelow) {
		err = regmap_read(radio->core->regmap,
				  SI476X_PROP_SEEK_BAND_BOTTOM,
				  &rangelow);
		if (err)
			goto unlock;
		rangelow = si476x_to_v4l2(radio->core, rangelow);
	}
	if (!rangehigh) {
		err = regmap_read(radio->core->regmap,
				  SI476X_PROP_SEEK_BAND_TOP,
				  &rangehigh);
		if (err)
			goto unlock;
		rangehigh = si476x_to_v4l2(radio->core, rangehigh);
	}

	if (rangelow > rangehigh) {
		err = -EINVAL;
		goto unlock;
	}

	if (si476x_radio_range_is_inside_of_the_band(rangelow, rangehigh,
						     SI476X_BAND_FM)) {
		func = SI476X_FUNC_FM_RECEIVER;

	} else if (si476x_core_has_am(radio->core) &&
		   si476x_radio_range_is_inside_of_the_band(rangelow, rangehigh,
							    SI476X_BAND_AM)) {
		func = SI476X_FUNC_AM_RECEIVER;
	} else {
		err = -EINVAL;
		goto unlock;
	}

	err = si476x_radio_change_func(radio, func);
	if (err < 0)
		goto unlock;

	if (seek->rangehigh) {
		err = regmap_write(radio->core->regmap,
				   SI476X_PROP_SEEK_BAND_TOP,
				   v4l2_to_si476x(radio->core,
						  seek->rangehigh));
		if (err)
			goto unlock;
	}
	if (seek->rangelow) {
		err = regmap_write(radio->core->regmap,
				   SI476X_PROP_SEEK_BAND_BOTTOM,
				   v4l2_to_si476x(radio->core,
						  seek->rangelow));
		if (err)
			goto unlock;
	}
	if (seek->spacing) {
		err = regmap_write(radio->core->regmap,
				     SI476X_PROP_SEEK_FREQUENCY_SPACING,
				     v4l2_to_si476x(radio->core,
						    seek->spacing));
		if (err)
			goto unlock;
	}

	err = radio->ops->seek_start(radio->core,
				     seek->seek_upward,
				     seek->wrap_around);
unlock:
	si476x_core_unlock(radio->core);



	return err;
}