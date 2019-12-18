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
struct pwm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 struct pwm_device* ERR_PTR (int) ; 
 int MAX_PWMS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pwm_device_request (struct pwm_device*,char const*) ; 
 int /*<<< orphan*/  pwm_lock ; 
 struct pwm_device* pwm_to_device (int) ; 

struct pwm_device *pwm_request(int pwm, const char *label)
{
	struct pwm_device *dev;
	int err;

	if (pwm < 0 || pwm >= MAX_PWMS)
		return ERR_PTR(-EINVAL);

	mutex_lock(&pwm_lock);

	dev = pwm_to_device(pwm);
	if (!dev) {
		dev = ERR_PTR(-EPROBE_DEFER);
		goto out;
	}

	err = pwm_device_request(dev, label);
	if (err < 0)
		dev = ERR_PTR(err);

out:
	mutex_unlock(&pwm_lock);

	return dev;
}