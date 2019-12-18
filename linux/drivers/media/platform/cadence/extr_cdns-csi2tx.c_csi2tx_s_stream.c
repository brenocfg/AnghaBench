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
struct csi2tx_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int csi2tx_start (struct csi2tx_priv*) ; 
 int /*<<< orphan*/  csi2tx_stop (struct csi2tx_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct csi2tx_priv* v4l2_subdev_to_csi2tx (struct v4l2_subdev*) ; 

__attribute__((used)) static int csi2tx_s_stream(struct v4l2_subdev *subdev, int enable)
{
	struct csi2tx_priv *csi2tx = v4l2_subdev_to_csi2tx(subdev);
	int ret = 0;

	mutex_lock(&csi2tx->lock);

	if (enable) {
		/*
		 * If we're not the first users, there's no need to
		 * enable the whole controller.
		 */
		if (!csi2tx->count) {
			ret = csi2tx_start(csi2tx);
			if (ret)
				goto out;
		}

		csi2tx->count++;
	} else {
		csi2tx->count--;

		/*
		 * Let the last user turn off the lights.
		 */
		if (!csi2tx->count)
			csi2tx_stop(csi2tx);
	}

out:
	mutex_unlock(&csi2tx->lock);
	return ret;
}