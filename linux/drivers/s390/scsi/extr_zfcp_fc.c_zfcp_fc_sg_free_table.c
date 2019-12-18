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
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 scalar_t__ sg_virt (struct scatterlist*) ; 

__attribute__((used)) static void zfcp_fc_sg_free_table(struct scatterlist *sg, int count)
{
	int i;

	for (i = 0; i < count; i++, sg = sg_next(sg))
		if (sg)
			free_page((unsigned long) sg_virt(sg));
		else
			break;
}