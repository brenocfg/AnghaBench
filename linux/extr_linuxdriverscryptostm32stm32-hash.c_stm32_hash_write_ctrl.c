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
typedef  int u32 ;
struct stm32_hash_request_ctx {int flags; int data_type; } ;
struct stm32_hash_dev {int flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  req; } ;
struct stm32_hash_ctx {scalar_t__ keylen; } ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_CR ; 
 int HASH_CR_ALGO_MD5 ; 
 int HASH_CR_ALGO_SHA1 ; 
 int HASH_CR_ALGO_SHA224 ; 
 int HASH_CR_ALGO_SHA256 ; 
 int HASH_CR_DATATYPE_POS ; 
 int HASH_CR_INIT ; 
 int HASH_CR_LKEY ; 
 int HASH_CR_MODE ; 
 int HASH_DCIE ; 
 int HASH_FLAGS_ALGO_MASK ; 
 int HASH_FLAGS_HMAC ; 
 int HASH_FLAGS_INIT ; 
#define  HASH_FLAGS_MD5 131 
#define  HASH_FLAGS_SHA1 130 
#define  HASH_FLAGS_SHA224 129 
#define  HASH_FLAGS_SHA256 128 
 int /*<<< orphan*/  HASH_IMR ; 
 scalar_t__ HASH_LONG_KEY ; 
 struct stm32_hash_request_ctx* ahash_request_ctx (int /*<<< orphan*/ ) ; 
 struct stm32_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stm32_hash_write (struct stm32_hash_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stm32_hash_write_ctrl(struct stm32_hash_dev *hdev)
{
	struct stm32_hash_request_ctx *rctx = ahash_request_ctx(hdev->req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(hdev->req);
	struct stm32_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	u32 reg = HASH_CR_INIT;

	if (!(hdev->flags & HASH_FLAGS_INIT)) {
		switch (rctx->flags & HASH_FLAGS_ALGO_MASK) {
		case HASH_FLAGS_MD5:
			reg |= HASH_CR_ALGO_MD5;
			break;
		case HASH_FLAGS_SHA1:
			reg |= HASH_CR_ALGO_SHA1;
			break;
		case HASH_FLAGS_SHA224:
			reg |= HASH_CR_ALGO_SHA224;
			break;
		case HASH_FLAGS_SHA256:
			reg |= HASH_CR_ALGO_SHA256;
			break;
		default:
			reg |= HASH_CR_ALGO_MD5;
		}

		reg |= (rctx->data_type << HASH_CR_DATATYPE_POS);

		if (rctx->flags & HASH_FLAGS_HMAC) {
			hdev->flags |= HASH_FLAGS_HMAC;
			reg |= HASH_CR_MODE;
			if (ctx->keylen > HASH_LONG_KEY)
				reg |= HASH_CR_LKEY;
		}

		stm32_hash_write(hdev, HASH_IMR, HASH_DCIE);

		stm32_hash_write(hdev, HASH_CR, reg);

		hdev->flags |= HASH_FLAGS_INIT;

		dev_dbg(hdev->dev, "Write Control %x\n", reg);
	}
}