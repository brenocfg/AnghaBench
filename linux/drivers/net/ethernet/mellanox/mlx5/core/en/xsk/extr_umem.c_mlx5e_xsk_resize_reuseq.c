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
typedef  int /*<<< orphan*/  u32 ;
struct xdp_umem_fq_reuse {int dummy; } ;
struct xdp_umem {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xsk_reuseq_free (int /*<<< orphan*/ ) ; 
 struct xdp_umem_fq_reuse* xsk_reuseq_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsk_reuseq_swap (struct xdp_umem*,struct xdp_umem_fq_reuse*) ; 

int mlx5e_xsk_resize_reuseq(struct xdp_umem *umem, u32 nentries)
{
	struct xdp_umem_fq_reuse *reuseq;

	reuseq = xsk_reuseq_prepare(nentries);
	if (unlikely(!reuseq))
		return -ENOMEM;
	xsk_reuseq_free(xsk_reuseq_swap(umem, reuseq));

	return 0;
}