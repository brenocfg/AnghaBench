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
typedef  int /*<<< orphan*/  u32 ;
struct stm32_hash_dev {int /*<<< orphan*/  req; } ;
struct stm32_hash_ctx {int keylen; void* key; } ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  HASH_DIN ; 
 int /*<<< orphan*/  HASH_STR ; 
 int /*<<< orphan*/  HASH_STR_DCAL ; 
 struct stm32_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_hash_read (struct stm32_hash_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_hash_set_nblw (struct stm32_hash_dev*,int) ; 
 int /*<<< orphan*/  stm32_hash_write (struct stm32_hash_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_hash_write_key(struct stm32_hash_dev *hdev)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(hdev->req);
	struct stm32_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	u32 reg;
	int keylen = ctx->keylen;
	void *key = ctx->key;

	if (keylen) {
		stm32_hash_set_nblw(hdev, keylen);

		while (keylen > 0) {
			stm32_hash_write(hdev, HASH_DIN, *(u32 *)key);
			keylen -= 4;
			key += 4;
		}

		reg = stm32_hash_read(hdev, HASH_STR);
		reg |= HASH_STR_DCAL;
		stm32_hash_write(hdev, HASH_STR, reg);

		return -EINPROGRESS;
	}

	return 0;
}