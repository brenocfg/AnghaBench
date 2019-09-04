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
struct atmel_aes_gcm_ctx {int (* ghash_resume ) (struct atmel_aes_dev*) ;int /*<<< orphan*/  ghash_out; } ;
struct atmel_aes_dev {scalar_t__ datalen; int data; int (* resume ) (struct atmel_aes_dev*) ;int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  AES_GHASHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AES_IDATAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AES_IER ; 
 int AES_INT_DATARDY ; 
 int /*<<< orphan*/  AES_ISR ; 
 int EINPROGRESS ; 
 struct atmel_aes_gcm_ctx* atmel_aes_gcm_ctx_cast (int /*<<< orphan*/ ) ; 
 int atmel_aes_read (struct atmel_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_read_block (struct atmel_aes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_write (struct atmel_aes_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atmel_aes_write_block (struct atmel_aes_dev*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct atmel_aes_dev*) ; 

__attribute__((used)) static int atmel_aes_gcm_ghash_finalize(struct atmel_aes_dev *dd)
{
	struct atmel_aes_gcm_ctx *ctx = atmel_aes_gcm_ctx_cast(dd->ctx);
	u32 isr;

	/* Write data into the Input Data Registers. */
	while (dd->datalen > 0) {
		atmel_aes_write_block(dd, AES_IDATAR(0), dd->data);
		dd->data += 4;
		dd->datalen -= AES_BLOCK_SIZE;

		isr = atmel_aes_read(dd, AES_ISR);
		if (!(isr & AES_INT_DATARDY)) {
			dd->resume = atmel_aes_gcm_ghash_finalize;
			atmel_aes_write(dd, AES_IER, AES_INT_DATARDY);
			return -EINPROGRESS;
		}
	}

	/* Read the computed hash from GHASHRx. */
	atmel_aes_read_block(dd, AES_GHASHR(0), ctx->ghash_out);

	return ctx->ghash_resume(dd);
}