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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct crypto_aead {int dummy; } ;
struct atmel_aes_reqctx {int dummy; } ;
struct atmel_aes_gcm_ctx {int /*<<< orphan*/ * j0; } ;
struct atmel_aes_dev {size_t buflen; int /*<<< orphan*/ * buf; int /*<<< orphan*/  areq; int /*<<< orphan*/  ctx; } ;
struct aead_request {void* iv; } ;

/* Variables and functions */
 size_t AES_BLOCK_SIZE ; 
 int EINVAL ; 
 size_t GCM_AES_IV_SIZE ; 
 struct aead_request* aead_request_cast (int /*<<< orphan*/ ) ; 
 struct atmel_aes_reqctx* aead_request_ctx (struct aead_request*) ; 
 int atmel_aes_complete (struct atmel_aes_dev*,int) ; 
 struct atmel_aes_gcm_ctx* atmel_aes_gcm_ctx_cast (int /*<<< orphan*/ ) ; 
 int atmel_aes_gcm_ghash (struct atmel_aes_dev*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int (*) (struct atmel_aes_dev*)) ; 
 int atmel_aes_gcm_process (struct atmel_aes_dev*) ; 
 int atmel_aes_hw_init (struct atmel_aes_dev*) ; 
 size_t atmel_aes_padlen (size_t,size_t) ; 
 int /*<<< orphan*/  atmel_aes_set_mode (struct atmel_aes_dev*,struct atmel_aes_reqctx*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (size_t) ; 
 size_t crypto_aead_ivsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int atmel_aes_gcm_start(struct atmel_aes_dev *dd)
{
	struct atmel_aes_gcm_ctx *ctx = atmel_aes_gcm_ctx_cast(dd->ctx);
	struct aead_request *req = aead_request_cast(dd->areq);
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct atmel_aes_reqctx *rctx = aead_request_ctx(req);
	size_t ivsize = crypto_aead_ivsize(tfm);
	size_t datalen, padlen;
	const void *iv = req->iv;
	u8 *data = dd->buf;
	int err;

	atmel_aes_set_mode(dd, rctx);

	err = atmel_aes_hw_init(dd);
	if (err)
		return atmel_aes_complete(dd, err);

	if (likely(ivsize == GCM_AES_IV_SIZE)) {
		memcpy(ctx->j0, iv, ivsize);
		ctx->j0[3] = cpu_to_be32(1);
		return atmel_aes_gcm_process(dd);
	}

	padlen = atmel_aes_padlen(ivsize, AES_BLOCK_SIZE);
	datalen = ivsize + padlen + AES_BLOCK_SIZE;
	if (datalen > dd->buflen)
		return atmel_aes_complete(dd, -EINVAL);

	memcpy(data, iv, ivsize);
	memset(data + ivsize, 0, padlen + sizeof(u64));
	((u64 *)(data + datalen))[-1] = cpu_to_be64(ivsize * 8);

	return atmel_aes_gcm_ghash(dd, (const u32 *)data, datalen,
				   NULL, ctx->j0, atmel_aes_gcm_process);
}