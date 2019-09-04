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
struct shash_desc {int dummy; } ;
struct sha256_state {unsigned int count; scalar_t__ buf; } ;

/* Variables and functions */
 unsigned int SHA256_BLOCK_SIZE ; 
 int /*<<< orphan*/  __sha256_sparc64_update (struct sha256_state*,int /*<<< orphan*/  const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,unsigned int) ; 
 struct sha256_state* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int sha256_sparc64_update(struct shash_desc *desc, const u8 *data,
				 unsigned int len)
{
	struct sha256_state *sctx = shash_desc_ctx(desc);
	unsigned int partial = sctx->count % SHA256_BLOCK_SIZE;

	/* Handle the fast case right here */
	if (partial + len < SHA256_BLOCK_SIZE) {
		sctx->count += len;
		memcpy(sctx->buf + partial, data, len);
	} else
		__sha256_sparc64_update(sctx, data, len, partial);

	return 0;
}