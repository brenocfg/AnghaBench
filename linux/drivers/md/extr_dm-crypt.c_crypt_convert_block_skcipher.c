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
struct skcipher_request {int dummy; } ;
struct scatterlist {int dummy; } ;
struct dm_crypt_request {int iv_sector; struct scatterlist* sg_out; struct scatterlist* sg_in; struct convert_context* ctx; } ;
struct crypt_config {int sector_size; int sector_shift; int iv_offset; TYPE_1__* iv_gen_ops; int /*<<< orphan*/  iv_size; int /*<<< orphan*/  integrity_iv_size; int /*<<< orphan*/  cipher_flags; } ;
struct convert_context {int cc_sector; int /*<<< orphan*/  iter_out; int /*<<< orphan*/  bio_out; int /*<<< orphan*/  iter_in; int /*<<< orphan*/  bio_in; } ;
struct bio_vec {int bv_len; int /*<<< orphan*/  bv_offset; int /*<<< orphan*/  bv_page; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_2__ {int (* generator ) (struct crypt_config*,int /*<<< orphan*/ *,struct dm_crypt_request*) ;int (* post ) (struct crypt_config*,int /*<<< orphan*/ *,struct dm_crypt_request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_IV_LARGE_SECTORS ; 
 int EIO ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  bio_advance_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ bio_data_dir (int /*<<< orphan*/ ) ; 
 struct bio_vec bio_iter_iovec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int crypto_skcipher_decrypt (struct skcipher_request*) ; 
 int crypto_skcipher_encrypt (struct skcipher_request*) ; 
 struct dm_crypt_request* dmreq_of_req (struct crypt_config*,struct skcipher_request*) ; 
 int /*<<< orphan*/ * iv_of_dmreq (struct crypt_config*,struct dm_crypt_request*) ; 
 int /*<<< orphan*/ * iv_tag_from_dmreq (struct crypt_config*,struct dm_crypt_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * org_iv_of_dmreq (struct crypt_config*,struct dm_crypt_request*) ; 
 int /*<<< orphan*/ * org_sector_of_dmreq (struct crypt_config*,struct dm_crypt_request*) ; 
 unsigned int* org_tag_of_dmreq (struct crypt_config*,struct dm_crypt_request*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,int,int /*<<< orphan*/ *) ; 
 int stub1 (struct crypt_config*,int /*<<< orphan*/ *,struct dm_crypt_request*) ; 
 int stub2 (struct crypt_config*,int /*<<< orphan*/ *,struct dm_crypt_request*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int crypt_convert_block_skcipher(struct crypt_config *cc,
					struct convert_context *ctx,
					struct skcipher_request *req,
					unsigned int tag_offset)
{
	struct bio_vec bv_in = bio_iter_iovec(ctx->bio_in, ctx->iter_in);
	struct bio_vec bv_out = bio_iter_iovec(ctx->bio_out, ctx->iter_out);
	struct scatterlist *sg_in, *sg_out;
	struct dm_crypt_request *dmreq;
	u8 *iv, *org_iv, *tag_iv;
	__le64 *sector;
	int r = 0;

	/* Reject unexpected unaligned bio. */
	if (unlikely(bv_in.bv_len & (cc->sector_size - 1)))
		return -EIO;

	dmreq = dmreq_of_req(cc, req);
	dmreq->iv_sector = ctx->cc_sector;
	if (test_bit(CRYPT_IV_LARGE_SECTORS, &cc->cipher_flags))
		dmreq->iv_sector >>= cc->sector_shift;
	dmreq->ctx = ctx;

	*org_tag_of_dmreq(cc, dmreq) = tag_offset;

	iv = iv_of_dmreq(cc, dmreq);
	org_iv = org_iv_of_dmreq(cc, dmreq);
	tag_iv = iv_tag_from_dmreq(cc, dmreq);

	sector = org_sector_of_dmreq(cc, dmreq);
	*sector = cpu_to_le64(ctx->cc_sector - cc->iv_offset);

	/* For skcipher we use only the first sg item */
	sg_in  = &dmreq->sg_in[0];
	sg_out = &dmreq->sg_out[0];

	sg_init_table(sg_in, 1);
	sg_set_page(sg_in, bv_in.bv_page, cc->sector_size, bv_in.bv_offset);

	sg_init_table(sg_out, 1);
	sg_set_page(sg_out, bv_out.bv_page, cc->sector_size, bv_out.bv_offset);

	if (cc->iv_gen_ops) {
		/* For READs use IV stored in integrity metadata */
		if (cc->integrity_iv_size && bio_data_dir(ctx->bio_in) != WRITE) {
			memcpy(org_iv, tag_iv, cc->integrity_iv_size);
		} else {
			r = cc->iv_gen_ops->generator(cc, org_iv, dmreq);
			if (r < 0)
				return r;
			/* Store generated IV in integrity metadata */
			if (cc->integrity_iv_size)
				memcpy(tag_iv, org_iv, cc->integrity_iv_size);
		}
		/* Working copy of IV, to be modified in crypto API */
		memcpy(iv, org_iv, cc->iv_size);
	}

	skcipher_request_set_crypt(req, sg_in, sg_out, cc->sector_size, iv);

	if (bio_data_dir(ctx->bio_in) == WRITE)
		r = crypto_skcipher_encrypt(req);
	else
		r = crypto_skcipher_decrypt(req);

	if (!r && cc->iv_gen_ops && cc->iv_gen_ops->post)
		r = cc->iv_gen_ops->post(cc, org_iv, dmreq);

	bio_advance_iter(ctx->bio_in, &ctx->iter_in, cc->sector_size);
	bio_advance_iter(ctx->bio_out, &ctx->iter_out, cc->sector_size);

	return r;
}