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
typedef  int /*<<< orphan*/  u64 ;
struct sha256_state {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_octeon_64bit_hash_dword (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void octeon_sha256_store_hash(struct sha256_state *sctx)
{
	u64 *hash = (u64 *)sctx->state;

	write_octeon_64bit_hash_dword(hash[0], 0);
	write_octeon_64bit_hash_dword(hash[1], 1);
	write_octeon_64bit_hash_dword(hash[2], 2);
	write_octeon_64bit_hash_dword(hash[3], 3);
}