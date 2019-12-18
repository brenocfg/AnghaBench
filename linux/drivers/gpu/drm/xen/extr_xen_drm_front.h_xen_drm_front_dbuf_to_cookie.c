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
typedef  uintptr_t u64 ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 xen_drm_front_dbuf_to_cookie(struct drm_gem_object *gem_obj)
{
	return (uintptr_t)gem_obj;
}