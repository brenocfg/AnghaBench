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
typedef  int u32 ;
struct nvme_ns {int lba_shift; int /*<<< orphan*/  queue; scalar_t__ noiob; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_queue_chunk_sectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rounddown_pow_of_two (int) ; 

__attribute__((used)) static void nvme_set_chunk_size(struct nvme_ns *ns)
{
	u32 chunk_size = (((u32)ns->noiob) << (ns->lba_shift - 9));
	blk_queue_chunk_sectors(ns->queue, rounddown_pow_of_two(chunk_size));
}