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
struct mspro_block_data {int /*<<< orphan*/  queue; } ;
struct memstick_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_start_hw_queues (int /*<<< orphan*/ ) ; 
 struct mspro_block_data* memstick_get_drvdata (struct memstick_dev*) ; 

__attribute__((used)) static void mspro_block_start(struct memstick_dev *card)
{
	struct mspro_block_data *msb = memstick_get_drvdata(card);

	blk_mq_start_hw_queues(msb->queue);
}