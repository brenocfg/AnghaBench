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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct sha1_state {int /*<<< orphan*/ * state; } ;
struct TYPE_2__ {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  memzero_explicit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_octeon_64bit_hash_dword (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void octeon_sha1_store_hash(struct sha1_state *sctx)
{
	u64 *hash = (u64 *)sctx->state;
	union {
		u32 word[2];
		u64 dword;
	} hash_tail = { { sctx->state[4], } };

	write_octeon_64bit_hash_dword(hash[0], 0);
	write_octeon_64bit_hash_dword(hash[1], 1);
	write_octeon_64bit_hash_dword(hash_tail.dword, 2);
	memzero_explicit(&hash_tail.word[0], sizeof(hash_tail.word[0]));
}