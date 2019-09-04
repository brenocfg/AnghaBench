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
struct sg_table {struct scatterlist* sgl; } ;
struct scatterlist {int /*<<< orphan*/  offset; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct scatterlist* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct scatterlist *
qce_sgtable_add(struct sg_table *sgt, struct scatterlist *new_sgl)
{
	struct scatterlist *sg = sgt->sgl, *sg_last = NULL;

	while (sg) {
		if (!sg_page(sg))
			break;
		sg = sg_next(sg);
	}

	if (!sg)
		return ERR_PTR(-EINVAL);

	while (new_sgl && sg) {
		sg_set_page(sg, sg_page(new_sgl), new_sgl->length,
			    new_sgl->offset);
		sg_last = sg;
		sg = sg_next(sg);
		new_sgl = sg_next(new_sgl);
	}

	return sg_last;
}