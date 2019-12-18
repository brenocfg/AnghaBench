#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct mlx5_mkey_seg {int flags; void* bsfs_octo_size; void* xlt_oct_size; int /*<<< orphan*/  len; void* flags_pd; void* qpn_mkey7_0; } ;
struct ib_mr {int rkey; } ;
struct TYPE_4__ {TYPE_1__* sig; } ;
struct TYPE_3__ {int sigerr_count; } ;

/* Variables and functions */
 int MLX5_MKC_ACCESS_MODE_KLMS ; 
 int MLX5_MKEY_BSF_EN ; 
 int MLX5_MKEY_BSF_OCTO_SIZE ; 
 int MLX5_MKEY_REMOTE_INVAL ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int get_umr_flags (int) ; 
 int get_xlt_octo (int) ; 
 int /*<<< orphan*/  memset (struct mlx5_mkey_seg*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* to_mmr (struct ib_mr*) ; 

__attribute__((used)) static void set_sig_mkey_segment(struct mlx5_mkey_seg *seg,
				 struct ib_mr *sig_mr, int access_flags,
				 u32 size, u32 length, u32 pdn)
{
	u32 sig_key = sig_mr->rkey;
	u8 sigerr = to_mmr(sig_mr)->sig->sigerr_count & 1;

	memset(seg, 0, sizeof(*seg));

	seg->flags = get_umr_flags(access_flags) | MLX5_MKC_ACCESS_MODE_KLMS;
	seg->qpn_mkey7_0 = cpu_to_be32((sig_key & 0xff) | 0xffffff00);
	seg->flags_pd = cpu_to_be32(MLX5_MKEY_REMOTE_INVAL | sigerr << 26 |
				    MLX5_MKEY_BSF_EN | pdn);
	seg->len = cpu_to_be64(length);
	seg->xlt_oct_size = cpu_to_be32(get_xlt_octo(size));
	seg->bsfs_octo_size = cpu_to_be32(MLX5_MKEY_BSF_OCTO_SIZE);
}