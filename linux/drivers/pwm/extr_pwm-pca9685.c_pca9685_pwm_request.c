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
struct pwm_chip {int /*<<< orphan*/  dev; } ;
struct pca9685 {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ pca9685_pwm_is_gpio (struct pca9685*,struct pwm_device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 struct pca9685* to_pca (struct pwm_chip*) ; 

__attribute__((used)) static int pca9685_pwm_request(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct pca9685 *pca = to_pca(chip);

	if (pca9685_pwm_is_gpio(pca, pwm))
		return -EBUSY;
	pm_runtime_get_sync(chip->dev);

	return 0;
}