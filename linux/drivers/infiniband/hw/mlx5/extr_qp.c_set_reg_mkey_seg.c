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
typedef  int u32 ;
struct mlx5_mkey_seg {int flags; void* xlt_oct_size; void* len; void* start_addr; void* flags_pd; void* qpn_mkey7_0; int /*<<< orphan*/  log2_page_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; int /*<<< orphan*/  iova; int /*<<< orphan*/  page_size; } ;
struct mlx5_ib_mr {int access_mode; TYPE_1__ ibmr; scalar_t__ meta_ndescs; int /*<<< orphan*/  ndescs; } ;

/* Variables and functions */
 int ALIGN (scalar_t__,int) ; 
 int MLX5_MKC_ACCESS_MODE_KLMS ; 
 int MLX5_MKC_ACCESS_MODE_MTT ; 
 int MLX5_MKEY_REMOTE_INVAL ; 
 void* cpu_to_be32 (int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int get_umr_flags (int) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mlx5_mkey_seg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_reg_mkey_seg(struct mlx5_mkey_seg *seg,
			     struct mlx5_ib_mr *mr,
			     u32 key, int access)
{
	int ndescs = ALIGN(mr->ndescs + mr->meta_ndescs, 8) >> 1;

	memset(seg, 0, sizeof(*seg));

	if (mr->access_mode == MLX5_MKC_ACCESS_MODE_MTT)
		seg->log2_page_size = ilog2(mr->ibmr.page_size);
	else if (mr->access_mode == MLX5_MKC_ACCESS_MODE_KLMS)
		/* KLMs take twice the size of MTTs */
		ndescs *= 2;

	seg->flags = get_umr_flags(access) | mr->access_mode;
	seg->qpn_mkey7_0 = cpu_to_be32((key & 0xff) | 0xffffff00);
	seg->flags_pd = cpu_to_be32(MLX5_MKEY_REMOTE_INVAL);
	seg->start_addr = cpu_to_be64(mr->ibmr.iova);
	seg->len = cpu_to_be64(mr->ibmr.length);
	seg->xlt_oct_size = cpu_to_be32(ndescs);
}