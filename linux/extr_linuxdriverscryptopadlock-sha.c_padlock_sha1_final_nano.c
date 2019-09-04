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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u8 ;
struct shash_desc {int dummy; } ;
struct sha1_state {int count; scalar_t__ state; } ;
typedef  int /*<<< orphan*/  bits ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  padlock_output_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  padlock_sha1_update_nano (struct shash_desc*,int const*,int) ; 
 scalar_t__ shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int padlock_sha1_final_nano(struct shash_desc *desc, u8 *out)
{
	struct sha1_state *state = (struct sha1_state *)shash_desc_ctx(desc);
	unsigned int partial, padlen;
	__be64 bits;
	static const u8 padding[64] = { 0x80, };

	bits = cpu_to_be64(state->count << 3);

	/* Pad out to 56 mod 64 */
	partial = state->count & 0x3f;
	padlen = (partial < 56) ? (56 - partial) : ((64+56) - partial);
	padlock_sha1_update_nano(desc, padding, padlen);

	/* Append length field bytes */
	padlock_sha1_update_nano(desc, (const u8 *)&bits, sizeof(bits));

	/* Swap to output */
	padlock_output_block((uint32_t *)(state->state), (uint32_t *)out, 5);

	return 0;
}