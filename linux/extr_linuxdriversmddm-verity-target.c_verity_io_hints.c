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
struct queue_limits {int logical_block_size; int physical_block_size; } ;
struct dm_verity {int data_dev_block_bits; } ;
struct dm_target {struct dm_verity* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_limits_io_min (struct queue_limits*,int) ; 

__attribute__((used)) static void verity_io_hints(struct dm_target *ti, struct queue_limits *limits)
{
	struct dm_verity *v = ti->private;

	if (limits->logical_block_size < 1 << v->data_dev_block_bits)
		limits->logical_block_size = 1 << v->data_dev_block_bits;

	if (limits->physical_block_size < 1 << v->data_dev_block_bits)
		limits->physical_block_size = 1 << v->data_dev_block_bits;

	blk_limits_io_min(limits, limits->logical_block_size);
}