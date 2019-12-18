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
struct platform_device_id {int dummy; } ;
struct of_device_id {struct platform_device_id const* data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  pwm_of_match ; 

__attribute__((used)) static const struct platform_device_id *pxa_pwm_get_id_dt(struct device *dev)
{
	const struct of_device_id *id = of_match_device(pwm_of_match, dev);

	return id ? id->data : NULL;
}