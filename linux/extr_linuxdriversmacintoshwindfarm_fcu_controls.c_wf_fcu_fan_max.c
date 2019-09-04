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
struct wf_fcu_fan {int /*<<< orphan*/  max; } ;
struct wf_control {struct wf_fcu_fan* priv; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */

__attribute__((used)) static s32 wf_fcu_fan_max(struct wf_control *ct)
{
	struct wf_fcu_fan *fan = ct->priv;

	return fan->max;
}