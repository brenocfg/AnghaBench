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
typedef  int /*<<< orphan*/  u8 ;
struct sha512_state {unsigned int* count; int /*<<< orphan*/  const* buf; } ;

/* Variables and functions */
 unsigned int SHA512_BLOCK_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  octeon_sha512_transform (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void __octeon_sha512_update(struct sha512_state *sctx, const u8 *data,
				   unsigned int len)
{
	unsigned int part_len;
	unsigned int index;
	unsigned int i;

	/* Compute number of bytes mod 128. */
	index = sctx->count[0] % SHA512_BLOCK_SIZE;

	/* Update number of bytes. */
	if ((sctx->count[0] += len) < len)
		sctx->count[1]++;

	part_len = SHA512_BLOCK_SIZE - index;

	/* Transform as many times as possible. */
	if (len >= part_len) {
		memcpy(&sctx->buf[index], data, part_len);
		octeon_sha512_transform(sctx->buf);

		for (i = part_len; i + SHA512_BLOCK_SIZE <= len;
			i += SHA512_BLOCK_SIZE)
			octeon_sha512_transform(&data[i]);

		index = 0;
	} else {
		i = 0;
	}

	/* Buffer remaining input. */
	memcpy(&sctx->buf[index], &data[i], len - i);
}