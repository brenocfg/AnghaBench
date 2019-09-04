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
struct spu_queue {int dummy; } ;
struct n2_crypto_chunk {int arr_len; unsigned long dest_paddr; unsigned long iv_paddr; TYPE_1__* arr; } ;
struct n2_cipher_context {int /*<<< orphan*/  key; int /*<<< orphan*/  enc_type; } ;
struct cwq_initial_entry {unsigned long src_addr; unsigned long auth_key_addr; unsigned long auth_iv_addr; unsigned long final_auth_state_addr; unsigned long enc_key_addr; unsigned long enc_iv_addr; unsigned long dest_addr; scalar_t__ control; } ;
struct crypto_tfm {int dummy; } ;
struct TYPE_2__ {unsigned long src_paddr; scalar_t__ src_len; } ;

/* Variables and functions */
 scalar_t__ CONTROL_END_OF_BLOCK ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ HV_EOK ; 
 int OPCODE_ENCRYPT ; 
 int OPCODE_INPLACE_BIT ; 
 unsigned long __pa (int /*<<< orphan*/ *) ; 
 scalar_t__ control_word_base (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 struct n2_cipher_context* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 struct cwq_initial_entry* spu_queue_alloc (struct spu_queue*,int) ; 
 struct cwq_initial_entry* spu_queue_next (struct spu_queue*,struct cwq_initial_entry*) ; 
 scalar_t__ spu_queue_submit (struct spu_queue*,struct cwq_initial_entry*) ; 

__attribute__((used)) static int __n2_crypt_chunk(struct crypto_tfm *tfm, struct n2_crypto_chunk *cp,
			    struct spu_queue *qp, bool encrypt)
{
	struct n2_cipher_context *ctx = crypto_tfm_ctx(tfm);
	struct cwq_initial_entry *ent;
	bool in_place;
	int i;

	ent = spu_queue_alloc(qp, cp->arr_len);
	if (!ent) {
		pr_info("queue_alloc() of %d fails\n",
			cp->arr_len);
		return -EBUSY;
	}

	in_place = (cp->dest_paddr == cp->arr[0].src_paddr);

	ent->control = control_word_base(cp->arr[0].src_len,
					 0, ctx->enc_type, 0, 0,
					 false, true, false, encrypt,
					 OPCODE_ENCRYPT |
					 (in_place ? OPCODE_INPLACE_BIT : 0));
	ent->src_addr = cp->arr[0].src_paddr;
	ent->auth_key_addr = 0UL;
	ent->auth_iv_addr = 0UL;
	ent->final_auth_state_addr = 0UL;
	ent->enc_key_addr = __pa(&ctx->key);
	ent->enc_iv_addr = cp->iv_paddr;
	ent->dest_addr = (in_place ? 0UL : cp->dest_paddr);

	for (i = 1; i < cp->arr_len; i++) {
		ent = spu_queue_next(qp, ent);

		ent->control = cp->arr[i].src_len - 1;
		ent->src_addr = cp->arr[i].src_paddr;
		ent->auth_key_addr = 0UL;
		ent->auth_iv_addr = 0UL;
		ent->final_auth_state_addr = 0UL;
		ent->enc_key_addr = 0UL;
		ent->enc_iv_addr = 0UL;
		ent->dest_addr = 0UL;
	}
	ent->control |= CONTROL_END_OF_BLOCK;

	return (spu_queue_submit(qp, ent) != HV_EOK) ? -EINVAL : 0;
}