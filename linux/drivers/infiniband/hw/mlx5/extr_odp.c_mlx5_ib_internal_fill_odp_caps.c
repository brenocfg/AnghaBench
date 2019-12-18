#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  xrc_odp_caps; int /*<<< orphan*/  rc_odp_caps; int /*<<< orphan*/  ud_odp_caps; } ;
struct ib_odp_caps {int /*<<< orphan*/  general_caps; TYPE_1__ per_transport_caps; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; int /*<<< orphan*/  odp_max_size; struct ib_odp_caps odp_caps; } ;
struct TYPE_8__ {int /*<<< orphan*/  srq_receive; int /*<<< orphan*/  atomic; int /*<<< orphan*/  read; int /*<<< orphan*/  write; int /*<<< orphan*/  receive; int /*<<< orphan*/  send; } ;
struct TYPE_7__ {int /*<<< orphan*/  srq_receive; int /*<<< orphan*/  send; } ;
struct TYPE_6__ {int /*<<< orphan*/  srq_receive; int /*<<< orphan*/  atomic; int /*<<< orphan*/  read; int /*<<< orphan*/  write; int /*<<< orphan*/  receive; int /*<<< orphan*/  send; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (scalar_t__) ; 
 int /*<<< orphan*/  IB_ODP_SUPPORT ; 
 int /*<<< orphan*/  IB_ODP_SUPPORT_ATOMIC ; 
 int /*<<< orphan*/  IB_ODP_SUPPORT_IMPLICIT ; 
 int /*<<< orphan*/  IB_ODP_SUPPORT_READ ; 
 int /*<<< orphan*/  IB_ODP_SUPPORT_RECV ; 
 int /*<<< orphan*/  IB_ODP_SUPPORT_SEND ; 
 int /*<<< orphan*/  IB_ODP_SUPPORT_SRQ_RECV ; 
 int /*<<< orphan*/  IB_ODP_SUPPORT_WRITE ; 
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_ODP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_MAX_UMR_SHIFT ; 
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  U64_MAX ; 
 int /*<<< orphan*/  fixed_buffer_size ; 
 int /*<<< orphan*/  memset (struct ib_odp_caps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_ib_can_use_umr (struct mlx5_ib_dev*,int) ; 
 int /*<<< orphan*/  null_mkey ; 
 int /*<<< orphan*/  pg ; 
 TYPE_4__ rc_odp_caps ; 
 TYPE_3__ ud_odp_caps ; 
 int /*<<< orphan*/  umr_extended_translation_offset ; 
 int /*<<< orphan*/  umr_indirect_mkey_disabled ; 
 TYPE_2__ xrc_odp_caps ; 

void mlx5_ib_internal_fill_odp_caps(struct mlx5_ib_dev *dev)
{
	struct ib_odp_caps *caps = &dev->odp_caps;

	memset(caps, 0, sizeof(*caps));

	if (!MLX5_CAP_GEN(dev->mdev, pg) ||
	    !mlx5_ib_can_use_umr(dev, true))
		return;

	caps->general_caps = IB_ODP_SUPPORT;

	if (MLX5_CAP_GEN(dev->mdev, umr_extended_translation_offset))
		dev->odp_max_size = U64_MAX;
	else
		dev->odp_max_size = BIT_ULL(MLX5_MAX_UMR_SHIFT + PAGE_SHIFT);

	if (MLX5_CAP_ODP(dev->mdev, ud_odp_caps.send))
		caps->per_transport_caps.ud_odp_caps |= IB_ODP_SUPPORT_SEND;

	if (MLX5_CAP_ODP(dev->mdev, ud_odp_caps.srq_receive))
		caps->per_transport_caps.ud_odp_caps |= IB_ODP_SUPPORT_SRQ_RECV;

	if (MLX5_CAP_ODP(dev->mdev, rc_odp_caps.send))
		caps->per_transport_caps.rc_odp_caps |= IB_ODP_SUPPORT_SEND;

	if (MLX5_CAP_ODP(dev->mdev, rc_odp_caps.receive))
		caps->per_transport_caps.rc_odp_caps |= IB_ODP_SUPPORT_RECV;

	if (MLX5_CAP_ODP(dev->mdev, rc_odp_caps.write))
		caps->per_transport_caps.rc_odp_caps |= IB_ODP_SUPPORT_WRITE;

	if (MLX5_CAP_ODP(dev->mdev, rc_odp_caps.read))
		caps->per_transport_caps.rc_odp_caps |= IB_ODP_SUPPORT_READ;

	if (MLX5_CAP_ODP(dev->mdev, rc_odp_caps.atomic))
		caps->per_transport_caps.rc_odp_caps |= IB_ODP_SUPPORT_ATOMIC;

	if (MLX5_CAP_ODP(dev->mdev, rc_odp_caps.srq_receive))
		caps->per_transport_caps.rc_odp_caps |= IB_ODP_SUPPORT_SRQ_RECV;

	if (MLX5_CAP_ODP(dev->mdev, xrc_odp_caps.send))
		caps->per_transport_caps.xrc_odp_caps |= IB_ODP_SUPPORT_SEND;

	if (MLX5_CAP_ODP(dev->mdev, xrc_odp_caps.receive))
		caps->per_transport_caps.xrc_odp_caps |= IB_ODP_SUPPORT_RECV;

	if (MLX5_CAP_ODP(dev->mdev, xrc_odp_caps.write))
		caps->per_transport_caps.xrc_odp_caps |= IB_ODP_SUPPORT_WRITE;

	if (MLX5_CAP_ODP(dev->mdev, xrc_odp_caps.read))
		caps->per_transport_caps.xrc_odp_caps |= IB_ODP_SUPPORT_READ;

	if (MLX5_CAP_ODP(dev->mdev, xrc_odp_caps.atomic))
		caps->per_transport_caps.xrc_odp_caps |= IB_ODP_SUPPORT_ATOMIC;

	if (MLX5_CAP_ODP(dev->mdev, xrc_odp_caps.srq_receive))
		caps->per_transport_caps.xrc_odp_caps |= IB_ODP_SUPPORT_SRQ_RECV;

	if (MLX5_CAP_GEN(dev->mdev, fixed_buffer_size) &&
	    MLX5_CAP_GEN(dev->mdev, null_mkey) &&
	    MLX5_CAP_GEN(dev->mdev, umr_extended_translation_offset) &&
	    !MLX5_CAP_GEN(dev->mdev, umr_indirect_mkey_disabled))
		caps->general_caps |= IB_ODP_SUPPORT_IMPLICIT;

	return;
}