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
struct mv_cesa_ahash_req {unsigned int len; } ;

/* Variables and functions */
 unsigned int CESA_HASH_BLOCK_SIZE_MSK ; 

__attribute__((used)) static int mv_cesa_ahash_pad_len(struct mv_cesa_ahash_req *creq)
{
	unsigned int index, padlen;

	index = creq->len & CESA_HASH_BLOCK_SIZE_MSK;
	padlen = (index < 56) ? (56 - index) : (64 + 56 - index);

	return padlen;
}