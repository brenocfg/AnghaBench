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
typedef  int /*<<< orphan*/  u16 ;
struct scatterlist {int dummy; } ;
struct msb_data {int pages_in_block; int page_size; int /*<<< orphan*/  block_size; int /*<<< orphan*/  block_buffer; } ;

/* Variables and functions */
 int EIO ; 
 int msb_read_page (struct msb_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct scatterlist*,int) ; 
 scalar_t__ msb_sg_compare_to_buffer (struct scatterlist*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msb_verify_block(struct msb_data *msb, u16 pba,
				struct scatterlist *orig_sg,  int offset)
{
	struct scatterlist sg;
	int page = 0, error;

	sg_init_one(&sg, msb->block_buffer, msb->block_size);

	while (page < msb->pages_in_block) {

		error = msb_read_page(msb, pba, page,
				NULL, &sg, page * msb->page_size);
		if (error)
			return error;
		page++;
	}

	if (msb_sg_compare_to_buffer(orig_sg, offset,
				msb->block_buffer, msb->block_size))
		return -EIO;
	return 0;
}