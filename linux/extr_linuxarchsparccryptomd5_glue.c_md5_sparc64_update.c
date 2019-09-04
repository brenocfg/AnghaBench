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
struct md5_state {unsigned int byte_count; scalar_t__ block; } ;

/* Variables and functions */
 unsigned int MD5_HMAC_BLOCK_SIZE ; 
 int /*<<< orphan*/  __md5_sparc64_update (struct md5_state*,int /*<<< orphan*/  const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 struct md5_state* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int md5_sparc64_update(struct shash_desc *desc, const u8 *data,
			      unsigned int len)
{
	struct md5_state *sctx = shash_desc_ctx(desc);
	unsigned int partial = sctx->byte_count % MD5_HMAC_BLOCK_SIZE;

	/* Handle the fast case right here */
	if (partial + len < MD5_HMAC_BLOCK_SIZE) {
		sctx->byte_count += len;
		memcpy((u8 *)sctx->block + partial, data, len);
	} else
		__md5_sparc64_update(sctx, data, len, partial);

	return 0;
}