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
struct pwm_ops {scalar_t__ apply; scalar_t__ disable; scalar_t__ enable; scalar_t__ config; } ;

/* Variables and functions */

__attribute__((used)) static bool pwm_ops_check(const struct pwm_ops *ops)
{
	/* driver supports legacy, non-atomic operation */
	if (ops->config && ops->enable && ops->disable)
		return true;

	/* driver supports atomic operation */
	if (ops->apply)
		return true;

	return false;
}