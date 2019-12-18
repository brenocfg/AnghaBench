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
struct scatterlist {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct bio_vec {int /*<<< orphan*/  bv_len; int /*<<< orphan*/  bv_offset; int /*<<< orphan*/  bv_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

__attribute__((used)) static void nvmet_file_init_bvec(struct bio_vec *bv, struct scatterlist *sg)
{
	bv->bv_page = sg_page(sg);
	bv->bv_offset = sg->offset;
	bv->bv_len = sg->length;
}