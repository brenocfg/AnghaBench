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
struct pwm_export {struct pwm_device* pwm; } ;
struct pwm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct pwm_export* child_to_pwm_export (struct device*) ; 

__attribute__((used)) static struct pwm_device *child_to_pwm_device(struct device *child)
{
	struct pwm_export *export = child_to_pwm_export(child);

	return export->pwm;
}