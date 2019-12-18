#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct sk_buff {scalar_t__ data; int /*<<< orphan*/  len; } ;
struct TYPE_3__ {int /*<<< orphan*/  mem_blocks; int /*<<< orphan*/  mem_block_size; } ;
struct ar9170 {int /*<<< orphan*/  mem_free_blocks; int /*<<< orphan*/  mem_lock; TYPE_1__ fw; int /*<<< orphan*/  mem_bitmap; int /*<<< orphan*/  mem_allocs; } ;
struct TYPE_4__ {scalar_t__ cookie; } ;
struct _carl9170_tx_superframe {TYPE_2__ s; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  atomic_add (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_sub_return (unsigned int,int /*<<< orphan*/ *) ; 
 int bitmap_find_free_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int carl9170_alloc_dev_space(struct ar9170 *ar, struct sk_buff *skb)
{
	struct _carl9170_tx_superframe *super = (void *) skb->data;
	unsigned int chunks;
	int cookie = -1;

	atomic_inc(&ar->mem_allocs);

	chunks = DIV_ROUND_UP(skb->len, ar->fw.mem_block_size);
	if (unlikely(atomic_sub_return(chunks, &ar->mem_free_blocks) < 0)) {
		atomic_add(chunks, &ar->mem_free_blocks);
		return -ENOSPC;
	}

	spin_lock_bh(&ar->mem_lock);
	cookie = bitmap_find_free_region(ar->mem_bitmap, ar->fw.mem_blocks, 0);
	spin_unlock_bh(&ar->mem_lock);

	if (unlikely(cookie < 0)) {
		atomic_add(chunks, &ar->mem_free_blocks);
		return -ENOSPC;
	}

	super = (void *) skb->data;

	/*
	 * Cookie #0 serves two special purposes:
	 *  1. The firmware might use it generate BlockACK frames
	 *     in responds of an incoming BlockAckReqs.
	 *
	 *  2. Prevent double-free bugs.
	 */
	super->s.cookie = (u8) cookie + 1;
	return 0;
}