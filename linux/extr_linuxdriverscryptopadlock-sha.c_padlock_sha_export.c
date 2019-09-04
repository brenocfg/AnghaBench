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
struct shash_desc {int dummy; } ;
struct padlock_sha_desc {int /*<<< orphan*/  fallback; } ;

/* Variables and functions */
 int crypto_shash_export (int /*<<< orphan*/ *,void*) ; 
 struct padlock_sha_desc* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int padlock_sha_export(struct shash_desc *desc, void *out)
{
	struct padlock_sha_desc *dctx = shash_desc_ctx(desc);

	return crypto_shash_export(&dctx->fallback, out);
}