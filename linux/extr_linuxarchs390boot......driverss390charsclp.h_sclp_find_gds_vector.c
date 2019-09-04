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
typedef  scalar_t__ u16 ;
struct gds_vector {int length; scalar_t__ gds_id; } ;

/* Variables and functions */

__attribute__((used)) static inline struct gds_vector *
sclp_find_gds_vector(void *start, void *end, u16 id)
{
	struct gds_vector *v;

	for (v = start; (void *) v < end; v = (void *) v + v->length)
		if (v->gds_id == id)
			return v;
	return NULL;
}