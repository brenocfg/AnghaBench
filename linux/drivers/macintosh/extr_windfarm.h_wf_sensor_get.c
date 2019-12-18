#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wf_sensor {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int (* get_value ) (struct wf_sensor*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (struct wf_sensor*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int wf_sensor_get(struct wf_sensor *sr, s32 *val)
{
	return sr->ops->get_value(sr, val);
}