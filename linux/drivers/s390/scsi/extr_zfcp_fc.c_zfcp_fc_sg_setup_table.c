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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fc_sg_free_table (struct scatterlist*,int) ; 

__attribute__((used)) static int zfcp_fc_sg_setup_table(struct scatterlist *sg, int count)
{
	void *addr;
	int i;

	sg_init_table(sg, count);
	for (i = 0; i < count; i++, sg = sg_next(sg)) {
		addr = (void *) get_zeroed_page(GFP_KERNEL);
		if (!addr) {
			zfcp_fc_sg_free_table(sg, i);
			return -ENOMEM;
		}
		sg_set_buf(sg, addr, PAGE_SIZE);
	}
	return 0;
}