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
typedef  int u8 ;
struct shash_desc {int dummy; } ;
struct sha256_state {int count; int /*<<< orphan*/ * state; } ;
struct octeon_cop2_state {int dummy; } ;
typedef  int /*<<< orphan*/  bits ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  __octeon_sha256_update (struct sha256_state*,int const*,int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  memset (struct sha256_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  octeon_crypto_disable (struct octeon_cop2_state*,unsigned long) ; 
 unsigned long octeon_crypto_enable (struct octeon_cop2_state*) ; 
 int /*<<< orphan*/  octeon_sha256_read_hash (struct sha256_state*) ; 
 int /*<<< orphan*/  octeon_sha256_store_hash (struct sha256_state*) ; 
 struct sha256_state* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int octeon_sha256_final(struct shash_desc *desc, u8 *out)
{
	struct sha256_state *sctx = shash_desc_ctx(desc);
	static const u8 padding[64] = { 0x80, };
	struct octeon_cop2_state state;
	__be32 *dst = (__be32 *)out;
	unsigned int pad_len;
	unsigned long flags;
	unsigned int index;
	__be64 bits;
	int i;

	/* Save number of bits. */
	bits = cpu_to_be64(sctx->count << 3);

	/* Pad out to 56 mod 64. */
	index = sctx->count & 0x3f;
	pad_len = (index < 56) ? (56 - index) : ((64+56) - index);

	flags = octeon_crypto_enable(&state);
	octeon_sha256_store_hash(sctx);

	__octeon_sha256_update(sctx, padding, pad_len);

	/* Append length (before padding). */
	__octeon_sha256_update(sctx, (const u8 *)&bits, sizeof(bits));

	octeon_sha256_read_hash(sctx);
	octeon_crypto_disable(&state, flags);

	/* Store state in digest */
	for (i = 0; i < 8; i++)
		dst[i] = cpu_to_be32(sctx->state[i]);

	/* Zeroize sensitive information. */
	memset(sctx, 0, sizeof(*sctx));

	return 0;
}