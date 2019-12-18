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
struct sg_table {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 struct sg_table* ERR_PTR (int /*<<< orphan*/ ) ; 

struct sg_table *qxl_gem_prime_get_sg_table(struct drm_gem_object *obj)
{
	return ERR_PTR(-ENOSYS);
}