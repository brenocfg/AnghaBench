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
struct nes_mr {scalar_t__ npages; } ;
struct ib_mr {int dummy; } ;

/* Variables and functions */
 int ib_sg_to_pages (struct ib_mr*,struct scatterlist*,int,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_set_page ; 
 struct nes_mr* to_nesmr (struct ib_mr*) ; 

__attribute__((used)) static int nes_map_mr_sg(struct ib_mr *ibmr, struct scatterlist *sg,
			 int sg_nents, unsigned int *sg_offset)
{
	struct nes_mr *nesmr = to_nesmr(ibmr);

	nesmr->npages = 0;

	return ib_sg_to_pages(ibmr, sg, sg_nents, sg_offset, nes_set_page);
}