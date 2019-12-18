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
struct gds_vector {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDS_ID_CPMSU ; 
 int /*<<< orphan*/  sclp_eval_cpmsu (struct gds_vector*) ; 
 struct gds_vector* sclp_find_gds_vector (struct gds_vector*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sclp_eval_mdsmu(struct gds_vector *v)
{
	v = sclp_find_gds_vector(v + 1, (void *) v + v->length, GDS_ID_CPMSU);
	if (v)
		sclp_eval_cpmsu(v);
}