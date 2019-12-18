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
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct pwm_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct pwm_device*) ; 
 int /*<<< orphan*/  devm_pwm_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct pwm_device**) ; 
 struct pwm_device** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct pwm_device**) ; 
 struct pwm_device* of_pwm_get (struct device*,struct device_node*,char const*) ; 

struct pwm_device *devm_of_pwm_get(struct device *dev, struct device_node *np,
				   const char *con_id)
{
	struct pwm_device **ptr, *pwm;

	ptr = devres_alloc(devm_pwm_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	pwm = of_pwm_get(dev, np, con_id);
	if (!IS_ERR(pwm)) {
		*ptr = pwm;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return pwm;
}