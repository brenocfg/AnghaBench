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
struct shash_desc {struct crypto_shash* tfm; } ;
struct crypto_shash {int dummy; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I40IW_ERR_MPA_CRC ; 
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 struct crypto_shash* crypto_alloc_shash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (struct crypto_shash*) ; 
 scalar_t__ crypto_shash_descsize (struct crypto_shash*) ; 
 struct shash_desc* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 

enum i40iw_status_code i40iw_init_hash_desc(struct shash_desc **desc)
{
	struct crypto_shash *tfm;
	struct shash_desc *tdesc;

	tfm = crypto_alloc_shash("crc32c", 0, 0);
	if (IS_ERR(tfm))
		return I40IW_ERR_MPA_CRC;

	tdesc = kzalloc(sizeof(*tdesc) + crypto_shash_descsize(tfm),
			GFP_KERNEL);
	if (!tdesc) {
		crypto_free_shash(tfm);
		return I40IW_ERR_MPA_CRC;
	}
	tdesc->tfm = tfm;
	*desc = tdesc;

	return 0;
}