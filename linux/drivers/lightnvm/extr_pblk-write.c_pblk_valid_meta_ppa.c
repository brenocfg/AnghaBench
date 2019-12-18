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
typedef  scalar_t__ u64 ;
struct ppa_addr {int dummy; } ;
struct pblk_line {scalar_t__ meta_distance; int /*<<< orphan*/  blk_bitmap; } ;
struct pblk_c_ctx {int /*<<< orphan*/  lun_bitmap; } ;
struct pblk {struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int dummy; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct nvm_rq {int dummy; } ;

/* Variables and functions */
 struct ppa_addr addr_to_gen_ppa (struct pblk*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct pblk_c_ctx* nvm_rq_to_pdu (struct nvm_rq*) ; 
 struct pblk_line* pblk_line_get_data (struct pblk*) ; 
 scalar_t__ pblk_lookup_page (struct pblk*,struct pblk_line*) ; 
 int /*<<< orphan*/  pblk_ppa_comp (struct ppa_addr,struct ppa_addr) ; 
 int pblk_ppa_to_pos (struct nvm_geo*,struct ppa_addr) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool pblk_valid_meta_ppa(struct pblk *pblk,
				       struct pblk_line *meta_line,
				       struct nvm_rq *data_rqd)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct pblk_c_ctx *data_c_ctx = nvm_rq_to_pdu(data_rqd);
	struct pblk_line *data_line = pblk_line_get_data(pblk);
	struct ppa_addr ppa, ppa_opt;
	u64 paddr;
	int pos_opt;

	/* Schedule a metadata I/O that is half the distance from the data I/O
	 * with regards to the number of LUNs forming the pblk instance. This
	 * balances LUN conflicts across every I/O.
	 *
	 * When the LUN configuration changes (e.g., due to GC), this distance
	 * can align, which would result on metadata and data I/Os colliding. In
	 * this case, modify the distance to not be optimal, but move the
	 * optimal in the right direction.
	 */
	paddr = pblk_lookup_page(pblk, meta_line);
	ppa = addr_to_gen_ppa(pblk, paddr, 0);
	ppa_opt = addr_to_gen_ppa(pblk, paddr + data_line->meta_distance, 0);
	pos_opt = pblk_ppa_to_pos(geo, ppa_opt);

	if (test_bit(pos_opt, data_c_ctx->lun_bitmap) ||
				test_bit(pos_opt, data_line->blk_bitmap))
		return true;

	if (unlikely(pblk_ppa_comp(ppa_opt, ppa)))
		data_line->meta_distance--;

	return false;
}