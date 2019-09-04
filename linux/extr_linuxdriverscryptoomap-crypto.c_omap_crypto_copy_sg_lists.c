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
typedef  int u16 ;
struct scatterlist {int length; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OMAP_CRYPTO_FORCE_SINGLE_ENTRY ; 
 struct scatterlist* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_mark_end (struct scatterlist*) ; 
 int sg_nents (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_crypto_copy_sg_lists(int total, int bs,
				     struct scatterlist **sg,
				     struct scatterlist *new_sg, u16 flags)
{
	int n = sg_nents(*sg);
	struct scatterlist *tmp;

	if (!(flags & OMAP_CRYPTO_FORCE_SINGLE_ENTRY)) {
		new_sg = kmalloc_array(n, sizeof(*sg), GFP_KERNEL);
		if (!new_sg)
			return -ENOMEM;

		sg_init_table(new_sg, n);
	}

	tmp = new_sg;

	while (*sg && total) {
		int len = (*sg)->length;

		if (total < len)
			len = total;

		if (len > 0) {
			total -= len;
			sg_set_page(tmp, sg_page(*sg), len, (*sg)->offset);
			if (total <= 0)
				sg_mark_end(tmp);
			tmp = sg_next(tmp);
		}

		*sg = sg_next(*sg);
	}

	*sg = new_sg;

	return 0;
}