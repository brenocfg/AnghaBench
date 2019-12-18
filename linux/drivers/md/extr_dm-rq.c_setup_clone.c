#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request {struct dm_rq_target_io* end_io_data; int /*<<< orphan*/  end_io; } ;
struct dm_rq_target_io {struct request* clone; TYPE_1__* md; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  bs; } ;

/* Variables and functions */
 int blk_rq_prep_clone (struct request*,struct request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_rq_target_io*) ; 
 int /*<<< orphan*/  dm_rq_bio_constructor ; 
 int /*<<< orphan*/  end_clone_request ; 

__attribute__((used)) static int setup_clone(struct request *clone, struct request *rq,
		       struct dm_rq_target_io *tio, gfp_t gfp_mask)
{
	int r;

	r = blk_rq_prep_clone(clone, rq, &tio->md->bs, gfp_mask,
			      dm_rq_bio_constructor, tio);
	if (r)
		return r;

	clone->end_io = end_clone_request;
	clone->end_io_data = tio;

	tio->clone = clone;

	return 0;
}