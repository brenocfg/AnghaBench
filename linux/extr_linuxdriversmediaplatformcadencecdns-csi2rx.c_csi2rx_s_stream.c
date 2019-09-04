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
struct v4l2_subdev {int dummy; } ;
struct csi2rx_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int csi2rx_start (struct csi2rx_priv*) ; 
 int /*<<< orphan*/  csi2rx_stop (struct csi2rx_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct csi2rx_priv* v4l2_subdev_to_csi2rx (struct v4l2_subdev*) ; 

__attribute__((used)) static int csi2rx_s_stream(struct v4l2_subdev *subdev, int enable)
{
	struct csi2rx_priv *csi2rx = v4l2_subdev_to_csi2rx(subdev);
	int ret = 0;

	mutex_lock(&csi2rx->lock);

	if (enable) {
		/*
		 * If we're not the first users, there's no need to
		 * enable the whole controller.
		 */
		if (!csi2rx->count) {
			ret = csi2rx_start(csi2rx);
			if (ret)
				goto out;
		}

		csi2rx->count++;
	} else {
		csi2rx->count--;

		/*
		 * Let the last user turn off the lights.
		 */
		if (!csi2rx->count)
			csi2rx_stop(csi2rx);
	}

out:
	mutex_unlock(&csi2rx->lock);
	return ret;
}