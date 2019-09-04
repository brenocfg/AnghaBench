#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct vmac_tfm_ctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bytes; } ;
struct vmac_desc_ctx {unsigned int nonce_size; int partial_size; int /*<<< orphan*/ * partial; int /*<<< orphan*/  const* partial_words; TYPE_1__ nonce; } ;
struct shash_desc {int /*<<< orphan*/  tfm; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 unsigned int VMAC_NHBYTES ; 
 unsigned int VMAC_NONCEBYTES ; 
 struct vmac_tfm_ctx* crypto_shash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 unsigned int round_down (unsigned int,unsigned int) ; 
 struct vmac_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 
 int /*<<< orphan*/  vhash_blocks (struct vmac_tfm_ctx const*,struct vmac_desc_ctx*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int vmac_update(struct shash_desc *desc, const u8 *p, unsigned int len)
{
	const struct vmac_tfm_ctx *tctx = crypto_shash_ctx(desc->tfm);
	struct vmac_desc_ctx *dctx = shash_desc_ctx(desc);
	unsigned int n;

	/* Nonce is passed as first VMAC_NONCEBYTES bytes of data */
	if (dctx->nonce_size < VMAC_NONCEBYTES) {
		n = min(len, VMAC_NONCEBYTES - dctx->nonce_size);
		memcpy(&dctx->nonce.bytes[dctx->nonce_size], p, n);
		dctx->nonce_size += n;
		p += n;
		len -= n;
	}

	if (dctx->partial_size) {
		n = min(len, VMAC_NHBYTES - dctx->partial_size);
		memcpy(&dctx->partial[dctx->partial_size], p, n);
		dctx->partial_size += n;
		p += n;
		len -= n;
		if (dctx->partial_size == VMAC_NHBYTES) {
			vhash_blocks(tctx, dctx, dctx->partial_words, 1);
			dctx->partial_size = 0;
		}
	}

	if (len >= VMAC_NHBYTES) {
		n = round_down(len, VMAC_NHBYTES);
		/* TODO: 'p' may be misaligned here */
		vhash_blocks(tctx, dctx, (const __le64 *)p, n / VMAC_NHBYTES);
		p += n;
		len -= n;
	}

	if (len) {
		memcpy(dctx->partial, p, len);
		dctx->partial_size = len;
	}

	return 0;
}