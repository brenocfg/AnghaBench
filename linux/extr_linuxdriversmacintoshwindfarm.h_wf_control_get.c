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
struct wf_control {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int (* get_value ) (struct wf_control*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (struct wf_control*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int wf_control_get(struct wf_control *ct, s32 *val)
{
	return ct->ops->get_value(ct, val);
}