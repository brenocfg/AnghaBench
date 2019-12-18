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
struct gds_vector {int length; scalar_t__ gds_id; } ;

/* Variables and functions */
 scalar_t__ GDS_ID_TEXTCMD ; 
 int /*<<< orphan*/  sclp_eval_textcmd (struct gds_vector*) ; 

__attribute__((used)) static inline void sclp_eval_cpmsu(struct gds_vector *v)
{
	void *end;

	end = (void *) v + v->length;
	for (v = v + 1; (void *) v < end; v = (void *) v + v->length)
		if (v->gds_id == GDS_ID_TEXTCMD)
			sclp_eval_textcmd(v);
}