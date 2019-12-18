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
struct intel_rotation_info {TYPE_1__* plane; } ;
struct TYPE_2__ {unsigned int stride; unsigned int height; unsigned long offset; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long rotated_index(const struct intel_rotation_info *r,
				   unsigned int n,
				   unsigned int x,
				   unsigned int y)
{
	return (r->plane[n].stride * (r->plane[n].height - y - 1) +
		r->plane[n].offset + x);
}