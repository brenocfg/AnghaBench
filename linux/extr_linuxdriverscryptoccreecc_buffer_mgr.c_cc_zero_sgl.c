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
typedef  int u32 ;
struct scatterlist {scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_virt (struct scatterlist*) ; 

void cc_zero_sgl(struct scatterlist *sgl, u32 data_len)
{
	struct scatterlist *current_sg = sgl;
	int sg_index = 0;

	while (sg_index <= data_len) {
		if (!current_sg) {
			/* reached the end of the sgl --> just return back */
			return;
		}
		memset(sg_virt(current_sg), 0, current_sg->length);
		sg_index += current_sg->length;
		current_sg = sg_next(current_sg);
	}
}