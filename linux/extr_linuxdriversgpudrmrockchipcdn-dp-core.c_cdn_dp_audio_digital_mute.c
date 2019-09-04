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
struct device {int dummy; } ;
struct cdn_dp_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int ENODEV ; 
 int cdn_dp_audio_mute (struct cdn_dp_device*,int) ; 
 struct cdn_dp_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdn_dp_audio_digital_mute(struct device *dev, void *data,
				     bool enable)
{
	struct cdn_dp_device *dp = dev_get_drvdata(dev);
	int ret;

	mutex_lock(&dp->lock);
	if (!dp->active) {
		ret = -ENODEV;
		goto out;
	}

	ret = cdn_dp_audio_mute(dp, enable);

out:
	mutex_unlock(&dp->lock);
	return ret;
}