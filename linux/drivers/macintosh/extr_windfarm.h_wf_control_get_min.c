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
struct TYPE_2__ {int /*<<< orphan*/  (* get_min ) (struct wf_control*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct wf_control*) ; 

__attribute__((used)) static inline s32 wf_control_get_min(struct wf_control *ct)
{
	return ct->ops->get_min(ct);
}