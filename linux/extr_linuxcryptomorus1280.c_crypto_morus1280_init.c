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
union morus1280_block_in {scalar_t__ bytes; } ;
typedef  int /*<<< orphan*/  u8 ;
struct morus1280_state {struct morus1280_block* s; } ;
struct morus1280_block {int /*<<< orphan*/ * words; } ;

/* Variables and functions */
 scalar_t__ MORUS1280_BLOCK_SIZE ; 
 unsigned int MORUS_BLOCK_WORDS ; 
 scalar_t__ MORUS_NONCE_SIZE ; 
 int /*<<< orphan*/  U64_C (int) ; 
 struct morus1280_block* crypto_morus1280_const ; 
 int /*<<< orphan*/  crypto_morus1280_load (struct morus1280_block*,scalar_t__) ; 
 int /*<<< orphan*/  crypto_morus1280_update (struct morus1280_state*,struct morus1280_block const*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void crypto_morus1280_init(struct morus1280_state *state,
				  const struct morus1280_block *key,
				  const u8 *iv)
{
	static const struct morus1280_block z = {};

	union morus1280_block_in tmp;
	unsigned int i;

	memcpy(tmp.bytes, iv, MORUS_NONCE_SIZE);
	memset(tmp.bytes + MORUS_NONCE_SIZE, 0,
	       MORUS1280_BLOCK_SIZE - MORUS_NONCE_SIZE);

	crypto_morus1280_load(&state->s[0], tmp.bytes);
	state->s[1] = *key;
	for (i = 0; i < MORUS_BLOCK_WORDS; i++)
		state->s[2].words[i] = U64_C(0xFFFFFFFFFFFFFFFF);
	state->s[3] = z;
	state->s[4] = crypto_morus1280_const[0];

	for (i = 0; i < 16; i++)
		crypto_morus1280_update(state, &z);

	for (i = 0; i < MORUS_BLOCK_WORDS; i++)
		state->s[1].words[i] ^= key->words[i];
}