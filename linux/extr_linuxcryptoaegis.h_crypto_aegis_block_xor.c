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
union aegis_block {int /*<<< orphan*/ * words64; } ;

/* Variables and functions */

__attribute__((used)) static void crypto_aegis_block_xor(union aegis_block *dst,
				   const union aegis_block *src)
{
	dst->words64[0] ^= src->words64[0];
	dst->words64[1] ^= src->words64[1];
}