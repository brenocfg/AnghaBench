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
struct list_head {int dummy; } ;
struct TYPE_2__ {int id; } ;
struct drm_display_mode {struct list_head head; TYPE_1__ base; } ;

/* Variables and functions */

void drm_mode_copy(struct drm_display_mode *dst, const struct drm_display_mode *src)
{
	int id = dst->base.id;
	struct list_head head = dst->head;

	*dst = *src;
	dst->base.id = id;
	dst->head = head;
}