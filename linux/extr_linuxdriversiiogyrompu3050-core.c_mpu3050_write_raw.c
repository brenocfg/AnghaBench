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
struct mpu3050 {int* calibration; int divisor; void* fullscale; int /*<<< orphan*/  lpf; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; int /*<<< orphan*/  scan_index; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int EINVAL ; 
 void* FS_1000_DPS ; 
 void* FS_2000_DPS ; 
 void* FS_250_DPS ; 
 void* FS_500_DPS ; 
 int /*<<< orphan*/  IIO_ANGL_VEL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int /*<<< orphan*/  LPF_188_HZ ; 
 int /*<<< orphan*/  LPF_256_HZ_NOLPF ; 
 int U16_MAX ; 
 struct mpu3050* iio_priv (struct iio_dev*) ; 
 int* mpu3050_fs_precision ; 

__attribute__((used)) static int mpu3050_write_raw(struct iio_dev *indio_dev,
			     const struct iio_chan_spec *chan,
			     int val, int val2, long mask)
{
	struct mpu3050 *mpu3050 = iio_priv(indio_dev);
	/*
	 * Couldn't figure out a way to precalculate these at compile time.
	 */
	unsigned int fs250 =
		DIV_ROUND_CLOSEST(mpu3050_fs_precision[0] * 1000000 * 2,
				  U16_MAX);
	unsigned int fs500 =
		DIV_ROUND_CLOSEST(mpu3050_fs_precision[1] * 1000000 * 2,
				  U16_MAX);
	unsigned int fs1000 =
		DIV_ROUND_CLOSEST(mpu3050_fs_precision[2] * 1000000 * 2,
				  U16_MAX);
	unsigned int fs2000 =
		DIV_ROUND_CLOSEST(mpu3050_fs_precision[3] * 1000000 * 2,
				  U16_MAX);

	switch (mask) {
	case IIO_CHAN_INFO_CALIBBIAS:
		if (chan->type != IIO_ANGL_VEL)
			return -EINVAL;
		mpu3050->calibration[chan->scan_index-1] = val;
		return 0;
	case IIO_CHAN_INFO_SAMP_FREQ:
		/*
		 * The max samplerate is 8000 Hz, the minimum
		 * 1000 / 256 ~= 4 Hz
		 */
		if (val < 4 || val > 8000)
			return -EINVAL;

		/*
		 * Above 1000 Hz we must turn off the digital low pass filter
		 * so we get a base frequency of 8kHz to the divider
		 */
		if (val > 1000) {
			mpu3050->lpf = LPF_256_HZ_NOLPF;
			mpu3050->divisor = DIV_ROUND_CLOSEST(8000, val) - 1;
			return 0;
		}

		mpu3050->lpf = LPF_188_HZ;
		mpu3050->divisor = DIV_ROUND_CLOSEST(1000, val) - 1;
		return 0;
	case IIO_CHAN_INFO_SCALE:
		if (chan->type != IIO_ANGL_VEL)
			return -EINVAL;
		/*
		 * We support +/-250, +/-500, +/-1000 and +/2000 deg/s
		 * which means we need to round to the closest radians
		 * which will be roughly +/-4.3, +/-8.7, +/-17.5, +/-35
		 * rad/s. The scale is then for the 16 bits used to cover
		 * it 2/(2^16) of that.
		 */

		/* Just too large, set the max range */
		if (val != 0) {
			mpu3050->fullscale = FS_2000_DPS;
			return 0;
		}

		/*
		 * Now we're dealing with fractions below zero in millirad/s
		 * do some integer interpolation and match with the closest
		 * fullscale in the table.
		 */
		if (val2 <= fs250 ||
		    val2 < ((fs500 + fs250) / 2))
			mpu3050->fullscale = FS_250_DPS;
		else if (val2 <= fs500 ||
			 val2 < ((fs1000 + fs500) / 2))
			mpu3050->fullscale = FS_500_DPS;
		else if (val2 <= fs1000 ||
			 val2 < ((fs2000 + fs1000) / 2))
			mpu3050->fullscale = FS_1000_DPS;
		else
			/* Catch-all */
			mpu3050->fullscale = FS_2000_DPS;
		return 0;
	default:
		break;
	}

	return -EINVAL;
}