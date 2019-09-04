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
struct ate_resource {int lowest_free_index; int /*<<< orphan*/ * ate; } ;

/* Variables and functions */
 int /*<<< orphan*/  mark_ate (struct ate_resource*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void free_ate_resource(struct ate_resource *ate_resource,
				     int start)
{
	mark_ate(ate_resource, start, ate_resource->ate[start], 0);
	if ((ate_resource->lowest_free_index > start) ||
	    (ate_resource->lowest_free_index < 0))
		ate_resource->lowest_free_index = start;
}