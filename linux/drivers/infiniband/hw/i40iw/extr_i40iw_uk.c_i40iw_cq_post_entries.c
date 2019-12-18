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
typedef  int /*<<< orphan*/  u8 ;
struct i40iw_cq_uk {int /*<<< orphan*/  cq_ring; int /*<<< orphan*/  shadow_area; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_RING_GETCURRENT_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40IW_RING_MOVE_TAIL_BY_COUNT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_64bit_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_cq_post_entries(struct i40iw_cq_uk *cq,
						    u8 count)
{
	I40IW_RING_MOVE_TAIL_BY_COUNT(cq->cq_ring, count);
	set_64bit_val(cq->shadow_area, 0,
		      I40IW_RING_GETCURRENT_HEAD(cq->cq_ring));
	return 0;
}