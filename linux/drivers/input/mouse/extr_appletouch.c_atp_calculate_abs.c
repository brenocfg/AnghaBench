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
struct atp {int* xy_acc; int* smooth; int* smooth_tmp; } ;

/* Variables and functions */
 int ATP_SCALE ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int threshold ; 

__attribute__((used)) static int atp_calculate_abs(struct atp *dev, int offset, int nb_sensors,
			     int fact, int *z, int *fingers)
{
	int i, pass;

	/*
	 * Use offset to point xy_sensors at the first value in dev->xy_acc
	 * for whichever dimension we're looking at this particular go-round.
	 */
	int *xy_sensors = dev->xy_acc + offset;

	/* values to calculate mean */
	int pcum = 0, psum = 0;
	int is_increasing = 0;

	*fingers = 0;

	for (i = 0; i < nb_sensors; i++) {
		if (xy_sensors[i] < threshold) {
			if (is_increasing)
				is_increasing = 0;

		/*
		 * Makes the finger detection more versatile.  For example,
		 * two fingers with no gap will be detected.  Also, my
		 * tests show it less likely to have intermittent loss
		 * of multiple finger readings while moving around (scrolling).
		 *
		 * Changes the multiple finger detection to counting humps on
		 * sensors (transitions from nonincreasing to increasing)
		 * instead of counting transitions from low sensors (no
		 * finger reading) to high sensors (finger above
		 * sensor)
		 *
		 * - Jason Parekh <jasonparekh@gmail.com>
		 */

		} else if (i < 1 ||
		    (!is_increasing && xy_sensors[i - 1] < xy_sensors[i])) {
			(*fingers)++;
			is_increasing = 1;
		} else if (i > 0 && (xy_sensors[i - 1] - xy_sensors[i] > threshold)) {
			is_increasing = 0;
		}
	}

	if (*fingers < 1)     /* No need to continue if no fingers are found. */
		return 0;

	/*
	 * Use a smoothed version of sensor data for movement calculations, to
	 * combat noise without needing to rely so heavily on a threshold.
	 * This improves tracking.
	 *
	 * The smoothed array is bigger than the original so that the smoothing
	 * doesn't result in edge values being truncated.
	 */

	memset(dev->smooth, 0, 4 * sizeof(dev->smooth[0]));
	/* Pull base values, scaled up to help avoid truncation errors. */
	for (i = 0; i < nb_sensors; i++)
		dev->smooth[i + 4] = xy_sensors[i] << ATP_SCALE;
	memset(&dev->smooth[nb_sensors + 4], 0, 4 * sizeof(dev->smooth[0]));

	for (pass = 0; pass < 4; pass++) {
		/* Handle edge. */
		dev->smooth_tmp[0] = (dev->smooth[0] + dev->smooth[1]) / 2;

		/* Average values with neighbors. */
		for (i = 1; i < nb_sensors + 7; i++)
			dev->smooth_tmp[i] = (dev->smooth[i - 1] +
					      dev->smooth[i] * 2 +
					      dev->smooth[i + 1]) / 4;

		/* Handle other edge. */
		dev->smooth_tmp[i] = (dev->smooth[i - 1] + dev->smooth[i]) / 2;

		memcpy(dev->smooth, dev->smooth_tmp, sizeof(dev->smooth));
	}

	for (i = 0; i < nb_sensors + 8; i++) {
		/*
		 * Skip values if they're small enough to be truncated to 0
		 * by scale. Mostly noise.
		 */
		if ((dev->smooth[i] >> ATP_SCALE) > 0) {
			pcum += dev->smooth[i] * i;
			psum += dev->smooth[i];
		}
	}

	if (psum > 0) {
		*z = psum >> ATP_SCALE;        /* Scale down pressure output. */
		return pcum * fact / psum;
	}

	return 0;
}