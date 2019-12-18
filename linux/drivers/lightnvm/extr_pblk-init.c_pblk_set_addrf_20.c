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
struct pblk_addrf {int sec_stripe; int ch_stripe; int lun_stripe; int sec_lun_stripe; int sec_ws_stripe; } ;
struct nvm_addrf {unsigned long long ch_len; unsigned long long lun_len; unsigned long long chk_len; unsigned long long sec_len; unsigned long long sec_offset; unsigned long long ch_offset; unsigned long long lun_offset; unsigned long long chk_offset; unsigned long long sec_mask; unsigned long long chk_mask; unsigned long long lun_mask; unsigned long long ch_mask; } ;
struct nvm_geo {int num_ch; int num_lun; int ws_opt; struct nvm_addrf addrf; } ;

/* Variables and functions */
 void* get_count_order (int) ; 

__attribute__((used)) static int pblk_set_addrf_20(struct nvm_geo *geo, struct nvm_addrf *adst,
			     struct pblk_addrf *udst)
{
	struct nvm_addrf *src = &geo->addrf;

	adst->ch_len = get_count_order(geo->num_ch);
	adst->lun_len = get_count_order(geo->num_lun);
	adst->chk_len = src->chk_len;
	adst->sec_len = src->sec_len;

	adst->sec_offset = 0;
	adst->ch_offset = adst->sec_len;
	adst->lun_offset = adst->ch_offset + adst->ch_len;
	adst->chk_offset = adst->lun_offset + adst->lun_len;

	adst->sec_mask = ((1ULL << adst->sec_len) - 1) << adst->sec_offset;
	adst->chk_mask = ((1ULL << adst->chk_len) - 1) << adst->chk_offset;
	adst->lun_mask = ((1ULL << adst->lun_len) - 1) << adst->lun_offset;
	adst->ch_mask = ((1ULL << adst->ch_len) - 1) << adst->ch_offset;

	udst->sec_stripe = geo->ws_opt;
	udst->ch_stripe = geo->num_ch;
	udst->lun_stripe = geo->num_lun;

	udst->sec_lun_stripe = udst->sec_stripe * udst->ch_stripe;
	udst->sec_ws_stripe = udst->sec_lun_stripe * udst->lun_stripe;

	return adst->chk_offset + adst->chk_len;
}