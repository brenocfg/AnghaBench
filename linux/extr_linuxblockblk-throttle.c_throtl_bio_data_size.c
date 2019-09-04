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
struct TYPE_2__ {unsigned int bi_size; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 scalar_t__ REQ_OP_DISCARD ; 
 scalar_t__ bio_op (struct bio*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline unsigned int throtl_bio_data_size(struct bio *bio)
{
	/* assume it's one sector */
	if (unlikely(bio_op(bio) == REQ_OP_DISCARD))
		return 512;
	return bio->bi_iter.bi_size;
}