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
struct shash_desc {int flags; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int crypto_shash_export (struct shash_desc*,void*) ; 
 struct shash_desc* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int hmac_export(struct shash_desc *pdesc, void *out)
{
	struct shash_desc *desc = shash_desc_ctx(pdesc);

	desc->flags = pdesc->flags & CRYPTO_TFM_REQ_MAY_SLEEP;

	return crypto_shash_export(desc, out);
}