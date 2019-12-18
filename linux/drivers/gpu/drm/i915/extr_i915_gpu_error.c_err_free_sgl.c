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
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct scatterlist* sg_chain_ptr (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_is_chain (struct scatterlist*) ; 
 scalar_t__ sg_is_last (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_virt (struct scatterlist*) ; 

__attribute__((used)) static void err_free_sgl(struct scatterlist *sgl)
{
	while (sgl) {
		struct scatterlist *sg;

		for (sg = sgl; !sg_is_chain(sg); sg++) {
			kfree(sg_virt(sg));
			if (sg_is_last(sg))
				break;
		}

		sg = sg_is_last(sg) ? NULL : sg_chain_ptr(sg);
		free_page((unsigned long)sgl);
		sgl = sg;
	}
}