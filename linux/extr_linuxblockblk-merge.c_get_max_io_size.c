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
struct request_queue {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 unsigned int blk_max_size_offset (struct request_queue*,int /*<<< orphan*/ ) ; 
 int queue_logical_block_size (struct request_queue*) ; 

__attribute__((used)) static inline unsigned get_max_io_size(struct request_queue *q,
				       struct bio *bio)
{
	unsigned sectors = blk_max_size_offset(q, bio->bi_iter.bi_sector);
	unsigned mask = queue_logical_block_size(q) - 1;

	/* aligned to logical block size */
	sectors &= ~(mask >> 9);

	return sectors;
}