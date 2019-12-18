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
struct wf_control {int dummy; } ;
struct smu_fan_control {int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 struct smu_fan_control* to_smu_fan (struct wf_control*) ; 

__attribute__((used)) static int smu_fan_get(struct wf_control *ct, s32 *value)
{
	struct smu_fan_control *fct = to_smu_fan(ct);
	*value = fct->value; /* todo: read from SMU */
	return 0;
}