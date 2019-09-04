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
typedef  union aegis_block {int dummy; } aegis_block ;
struct aegis_state {union aegis_block* blocks; } ;

/* Variables and functions */
 int AEGIS128_STATE_BLOCKS ; 
 int /*<<< orphan*/  crypto_aegis_aesenc (union aegis_block*,union aegis_block*,union aegis_block*) ; 

__attribute__((used)) static void crypto_aegis128_update(struct aegis_state *state)
{
	union aegis_block tmp;
	unsigned int i;

	tmp = state->blocks[AEGIS128_STATE_BLOCKS - 1];
	for (i = AEGIS128_STATE_BLOCKS - 1; i > 0; i--)
		crypto_aegis_aesenc(&state->blocks[i], &state->blocks[i - 1],
				    &state->blocks[i]);
	crypto_aegis_aesenc(&state->blocks[0], &tmp, &state->blocks[0]);
}