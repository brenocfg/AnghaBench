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
union aegis_chunk {int /*<<< orphan*/ * blocks; } ;
struct aegis_state {int /*<<< orphan*/ * blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_aegis128l_update (struct aegis_state*) ; 
 int /*<<< orphan*/  crypto_aegis_block_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crypto_aegis128l_update_a(struct aegis_state *state,
				      const union aegis_chunk *msg)
{
	crypto_aegis128l_update(state);
	crypto_aegis_block_xor(&state->blocks[0], &msg->blocks[0]);
	crypto_aegis_block_xor(&state->blocks[4], &msg->blocks[1]);
}