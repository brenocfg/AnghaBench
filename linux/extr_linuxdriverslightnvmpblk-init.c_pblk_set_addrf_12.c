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
struct pblk {int dummy; } ;
struct nvm_geo {int num_ch; int num_lun; int /*<<< orphan*/  addrf; } ;
struct nvm_addrf_12 {int ch_len; int lun_len; unsigned long long blk_len; unsigned long long pg_len; unsigned long long pln_len; unsigned long long sec_len; unsigned long long sec_offset; unsigned long long pln_offset; int ch_offset; int lun_offset; int pg_offset; unsigned long long blk_offset; unsigned long long sec_mask; unsigned long long pln_mask; unsigned long long ch_mask; unsigned long long lun_mask; unsigned long long pg_mask; unsigned long long blk_mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int get_count_order (int) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*) ; 

__attribute__((used)) static int pblk_set_addrf_12(struct pblk *pblk, struct nvm_geo *geo,
			     struct nvm_addrf_12 *dst)
{
	struct nvm_addrf_12 *src = (struct nvm_addrf_12 *)&geo->addrf;
	int power_len;

	/* Re-calculate channel and lun format to adapt to configuration */
	power_len = get_count_order(geo->num_ch);
	if (1 << power_len != geo->num_ch) {
		pblk_err(pblk, "supports only power-of-two channel config.\n");
		return -EINVAL;
	}
	dst->ch_len = power_len;

	power_len = get_count_order(geo->num_lun);
	if (1 << power_len != geo->num_lun) {
		pblk_err(pblk, "supports only power-of-two LUN config.\n");
		return -EINVAL;
	}
	dst->lun_len = power_len;

	dst->blk_len = src->blk_len;
	dst->pg_len = src->pg_len;
	dst->pln_len = src->pln_len;
	dst->sec_len = src->sec_len;

	dst->sec_offset = 0;
	dst->pln_offset = dst->sec_len;
	dst->ch_offset = dst->pln_offset + dst->pln_len;
	dst->lun_offset = dst->ch_offset + dst->ch_len;
	dst->pg_offset = dst->lun_offset + dst->lun_len;
	dst->blk_offset = dst->pg_offset + dst->pg_len;

	dst->sec_mask = ((1ULL << dst->sec_len) - 1) << dst->sec_offset;
	dst->pln_mask = ((1ULL << dst->pln_len) - 1) << dst->pln_offset;
	dst->ch_mask = ((1ULL << dst->ch_len) - 1) << dst->ch_offset;
	dst->lun_mask = ((1ULL << dst->lun_len) - 1) << dst->lun_offset;
	dst->pg_mask = ((1ULL << dst->pg_len) - 1) << dst->pg_offset;
	dst->blk_mask = ((1ULL << dst->blk_len) - 1) << dst->blk_offset;

	return dst->blk_offset + src->blk_len;
}