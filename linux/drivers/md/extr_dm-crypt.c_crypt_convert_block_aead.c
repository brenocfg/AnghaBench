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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u8 ;
struct dm_crypt_request {int iv_sector; int /*<<< orphan*/ * sg_out; int /*<<< orphan*/ * sg_in; struct convert_context* ctx; } ;
struct crypt_config {scalar_t__ integrity_iv_size; scalar_t__ iv_size; int sector_size; int sector_shift; int iv_offset; int integrity_tag_size; scalar_t__ on_disk_tag_size; TYPE_1__* iv_gen_ops; int /*<<< orphan*/  cipher_flags; } ;
struct convert_context {int cc_sector; int /*<<< orphan*/  iter_out; int /*<<< orphan*/  bio_out; int /*<<< orphan*/  iter_in; int /*<<< orphan*/  bio_in; } ;
struct bio_vec {int bv_len; int /*<<< orphan*/  bv_offset; int /*<<< orphan*/  bv_page; } ;
struct aead_request {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_2__ {int (* generator ) (struct crypt_config*,int /*<<< orphan*/ *,struct dm_crypt_request*) ;int (* post ) (struct crypt_config*,int /*<<< orphan*/ *,struct dm_crypt_request*) ;} ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CRYPT_IV_LARGE_SECTORS ; 
 int /*<<< orphan*/  DMERR_LIMIT (char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int EBADMSG ; 
 int EIO ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  aead_request_set_ad (struct aead_request*,int) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_advance_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ bio_data_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_devname (int /*<<< orphan*/ ,char*) ; 
 struct bio_vec bio_iter_iovec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int crypto_aead_decrypt (struct aead_request*) ; 
 int crypto_aead_encrypt (struct aead_request*) ; 
 struct dm_crypt_request* dmreq_of_req (struct crypt_config*,struct aead_request*) ; 
 int /*<<< orphan*/ * iv_of_dmreq (struct crypt_config*,struct dm_crypt_request*) ; 
 int /*<<< orphan*/ * iv_tag_from_dmreq (struct crypt_config*,struct dm_crypt_request*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * org_iv_of_dmreq (struct crypt_config*,struct dm_crypt_request*) ; 
 int /*<<< orphan*/ * org_sector_of_dmreq (struct crypt_config*,struct dm_crypt_request*) ; 
 unsigned int* org_tag_of_dmreq (struct crypt_config*,struct dm_crypt_request*) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sg_set_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct crypt_config*,int /*<<< orphan*/ *,struct dm_crypt_request*) ; 
 int stub2 (struct crypt_config*,int /*<<< orphan*/ *,struct dm_crypt_request*) ; 
 int /*<<< orphan*/ * tag_from_dmreq (struct crypt_config*,struct dm_crypt_request*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int crypt_convert_block_aead(struct crypt_config *cc,
				     struct convert_context *ctx,
				     struct aead_request *req,
				     unsigned int tag_offset)
{
	struct bio_vec bv_in = bio_iter_iovec(ctx->bio_in, ctx->iter_in);
	struct bio_vec bv_out = bio_iter_iovec(ctx->bio_out, ctx->iter_out);
	struct dm_crypt_request *dmreq;
	u8 *iv, *org_iv, *tag_iv, *tag;
	__le64 *sector;
	int r = 0;

	BUG_ON(cc->integrity_iv_size && cc->integrity_iv_size != cc->iv_size);

	/* Reject unexpected unaligned bio. */
	if (unlikely(bv_in.bv_len & (cc->sector_size - 1)))
		return -EIO;

	dmreq = dmreq_of_req(cc, req);
	dmreq->iv_sector = ctx->cc_sector;
	if (test_bit(CRYPT_IV_LARGE_SECTORS, &cc->cipher_flags))
		dmreq->iv_sector >>= cc->sector_shift;
	dmreq->ctx = ctx;

	*org_tag_of_dmreq(cc, dmreq) = tag_offset;

	sector = org_sector_of_dmreq(cc, dmreq);
	*sector = cpu_to_le64(ctx->cc_sector - cc->iv_offset);

	iv = iv_of_dmreq(cc, dmreq);
	org_iv = org_iv_of_dmreq(cc, dmreq);
	tag = tag_from_dmreq(cc, dmreq);
	tag_iv = iv_tag_from_dmreq(cc, dmreq);

	/* AEAD request:
	 *  |----- AAD -------|------ DATA -------|-- AUTH TAG --|
	 *  | (authenticated) | (auth+encryption) |              |
	 *  | sector_LE |  IV |  sector in/out    |  tag in/out  |
	 */
	sg_init_table(dmreq->sg_in, 4);
	sg_set_buf(&dmreq->sg_in[0], sector, sizeof(uint64_t));
	sg_set_buf(&dmreq->sg_in[1], org_iv, cc->iv_size);
	sg_set_page(&dmreq->sg_in[2], bv_in.bv_page, cc->sector_size, bv_in.bv_offset);
	sg_set_buf(&dmreq->sg_in[3], tag, cc->integrity_tag_size);

	sg_init_table(dmreq->sg_out, 4);
	sg_set_buf(&dmreq->sg_out[0], sector, sizeof(uint64_t));
	sg_set_buf(&dmreq->sg_out[1], org_iv, cc->iv_size);
	sg_set_page(&dmreq->sg_out[2], bv_out.bv_page, cc->sector_size, bv_out.bv_offset);
	sg_set_buf(&dmreq->sg_out[3], tag, cc->integrity_tag_size);

	if (cc->iv_gen_ops) {
		/* For READs use IV stored in integrity metadata */
		if (cc->integrity_iv_size && bio_data_dir(ctx->bio_in) != WRITE) {
			memcpy(org_iv, tag_iv, cc->iv_size);
		} else {
			r = cc->iv_gen_ops->generator(cc, org_iv, dmreq);
			if (r < 0)
				return r;
			/* Store generated IV in integrity metadata */
			if (cc->integrity_iv_size)
				memcpy(tag_iv, org_iv, cc->iv_size);
		}
		/* Working copy of IV, to be modified in crypto API */
		memcpy(iv, org_iv, cc->iv_size);
	}

	aead_request_set_ad(req, sizeof(uint64_t) + cc->iv_size);
	if (bio_data_dir(ctx->bio_in) == WRITE) {
		aead_request_set_crypt(req, dmreq->sg_in, dmreq->sg_out,
				       cc->sector_size, iv);
		r = crypto_aead_encrypt(req);
		if (cc->integrity_tag_size + cc->integrity_iv_size != cc->on_disk_tag_size)
			memset(tag + cc->integrity_tag_size + cc->integrity_iv_size, 0,
			       cc->on_disk_tag_size - (cc->integrity_tag_size + cc->integrity_iv_size));
	} else {
		aead_request_set_crypt(req, dmreq->sg_in, dmreq->sg_out,
				       cc->sector_size + cc->integrity_tag_size, iv);
		r = crypto_aead_decrypt(req);
	}

	if (r == -EBADMSG) {
		char b[BDEVNAME_SIZE];
		DMERR_LIMIT("%s: INTEGRITY AEAD ERROR, sector %llu", bio_devname(ctx->bio_in, b),
			    (unsigned long long)le64_to_cpu(*sector));
	}

	if (!r && cc->iv_gen_ops && cc->iv_gen_ops->post)
		r = cc->iv_gen_ops->post(cc, org_iv, dmreq);

	bio_advance_iter(ctx->bio_in, &ctx->iter_in, cc->sector_size);
	bio_advance_iter(ctx->bio_out, &ctx->iter_out, cc->sector_size);

	return r;
}