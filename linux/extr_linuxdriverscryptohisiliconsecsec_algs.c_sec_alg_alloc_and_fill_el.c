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
struct sec_bd_info {int w0; int w2; void* cipher_destin_addr_hi; void* cipher_destin_addr_lo; void* data_addr_hi; void* data_addr_lo; int /*<<< orphan*/  w1; int /*<<< orphan*/  w3; } ;
struct sec_request_el {int el_length; int /*<<< orphan*/  dma_in; int /*<<< orphan*/  in; int /*<<< orphan*/  dma_out; struct scatterlist* sgl_out; int /*<<< orphan*/  out; struct scatterlist* sgl_in; struct sec_bd_info req; } ;
struct sec_dev_info {int dummy; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct sec_request_el* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SEC_BD_W0_CIPHER_M ; 
 int SEC_BD_W0_CIPHER_S ; 
 int SEC_BD_W0_C_GRAN_SIZE_19_16_M ; 
 int SEC_BD_W0_C_GRAN_SIZE_19_16_S ; 
 int SEC_BD_W0_C_GRAN_SIZE_21_20_M ; 
 int SEC_BD_W0_C_GRAN_SIZE_21_20_S ; 
 int SEC_BD_W0_DE ; 
 int /*<<< orphan*/  SEC_BD_W1_ADDR_TYPE ; 
 int SEC_BD_W2_C_GRAN_SIZE_15_0_M ; 
 int SEC_BD_W2_C_GRAN_SIZE_15_0_S ; 
 int SEC_BD_W2_GRAN_NUM_M ; 
 int SEC_BD_W2_GRAN_NUM_S ; 
 int /*<<< orphan*/  SEC_BD_W3_CIPHER_LEN_OFFSET_M ; 
 int SEC_CIPHER_DECRYPT ; 
 int SEC_CIPHER_ENCRYPT ; 
 int /*<<< orphan*/  kfree (struct sec_request_el*) ; 
 struct sec_request_el* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct sec_bd_info*,struct sec_bd_info*,int) ; 
 int sec_alloc_and_fill_hw_sgl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct scatterlist*,int,struct sec_dev_info*) ; 
 int /*<<< orphan*/  sec_free_hw_sgl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sec_dev_info*) ; 
 void* upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sec_request_el
*sec_alg_alloc_and_fill_el(struct sec_bd_info *template, int encrypt,
			   int el_size, bool different_dest,
			   struct scatterlist *sgl_in, int n_ents_in,
			   struct scatterlist *sgl_out, int n_ents_out,
			   struct sec_dev_info *info)
{
	struct sec_request_el *el;
	struct sec_bd_info *req;
	int ret;

	el = kzalloc(sizeof(*el), GFP_KERNEL);
	if (!el)
		return ERR_PTR(-ENOMEM);
	el->el_length = el_size;
	req = &el->req;
	memcpy(req, template, sizeof(*req));

	req->w0 &= ~SEC_BD_W0_CIPHER_M;
	if (encrypt)
		req->w0 |= SEC_CIPHER_ENCRYPT << SEC_BD_W0_CIPHER_S;
	else
		req->w0 |= SEC_CIPHER_DECRYPT << SEC_BD_W0_CIPHER_S;

	req->w0 &= ~SEC_BD_W0_C_GRAN_SIZE_19_16_M;
	req->w0 |= ((el_size >> 16) << SEC_BD_W0_C_GRAN_SIZE_19_16_S) &
		SEC_BD_W0_C_GRAN_SIZE_19_16_M;

	req->w0 &= ~SEC_BD_W0_C_GRAN_SIZE_21_20_M;
	req->w0 |= ((el_size >> 20) << SEC_BD_W0_C_GRAN_SIZE_21_20_S) &
		SEC_BD_W0_C_GRAN_SIZE_21_20_M;

	/* Writing whole u32 so no need to take care of masking */
	req->w2 = ((1 << SEC_BD_W2_GRAN_NUM_S) & SEC_BD_W2_GRAN_NUM_M) |
		((el_size << SEC_BD_W2_C_GRAN_SIZE_15_0_S) &
		 SEC_BD_W2_C_GRAN_SIZE_15_0_M);

	req->w3 &= ~SEC_BD_W3_CIPHER_LEN_OFFSET_M;
	req->w1 |= SEC_BD_W1_ADDR_TYPE;

	el->sgl_in = sgl_in;

	ret = sec_alloc_and_fill_hw_sgl(&el->in, &el->dma_in, el->sgl_in,
					n_ents_in, info);
	if (ret)
		goto err_free_el;

	req->data_addr_lo = lower_32_bits(el->dma_in);
	req->data_addr_hi = upper_32_bits(el->dma_in);

	if (different_dest) {
		el->sgl_out = sgl_out;
		ret = sec_alloc_and_fill_hw_sgl(&el->out, &el->dma_out,
						el->sgl_out,
						n_ents_out, info);
		if (ret)
			goto err_free_hw_sgl_in;

		req->w0 |= SEC_BD_W0_DE;
		req->cipher_destin_addr_lo = lower_32_bits(el->dma_out);
		req->cipher_destin_addr_hi = upper_32_bits(el->dma_out);

	} else {
		req->w0 &= ~SEC_BD_W0_DE;
		req->cipher_destin_addr_lo = lower_32_bits(el->dma_in);
		req->cipher_destin_addr_hi = upper_32_bits(el->dma_in);
	}

	return el;

err_free_hw_sgl_in:
	sec_free_hw_sgl(el->in, el->dma_in, info);
err_free_el:
	kfree(el);

	return ERR_PTR(ret);
}