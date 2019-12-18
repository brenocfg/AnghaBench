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
struct ttm_buffer_object {scalar_t__ destroy; } ;

/* Variables and functions */
 scalar_t__ ttm_buffer_object_destroy ; 

__attribute__((used)) static bool drm_is_gem_vram(struct ttm_buffer_object *bo)
{
	return (bo->destroy == ttm_buffer_object_destroy);
}