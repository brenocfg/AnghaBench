#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rc_odp_caps; int /*<<< orphan*/  ud_odp_caps; } ;
struct ib_odp_caps {int /*<<< orphan*/  general_caps; TYPE_1__ per_transport_caps; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; int /*<<< orphan*/  odp_max_size; struct ib_odp_caps odp_caps; } ;
struct TYPE_6__ {int /*<<< orphan*/  atomic; int /*<<< orphan*/  read; int /*<<< orphan*/  write; int /*<<< orphan*/  receive; int /*<<< orphan*/  send; } ;
struct TYPE_5__ {int /*<<< orphan*/  send; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (scalar_t__) ; 
 int /*<<< orphan*/  IB_ODP_SUPPORT ; 
 int /*<<< orphan*/  IB_ODP_SUPPORT_ATOMIC ; 
 int /*<<< orphan*/  IB_ODP_SUPPORT_IMPLICIT ; 
 int /*<<< orphan*/  IB_ODP_SUPPORT_READ ; 
 int /*<<< orphan*/  IB_ODP_SUPPORT_RECV ; 
 int /*<<< orphan*/  IB_ODP_SUPPORT_SEND ; 
 int /*<<< orphan*/  IB_ODP_SUPPORT_WRITE ; 
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_ODP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_MAX_UMR_SHIFT ; 
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  U64_MAX ; 
 int /*<<< orphan*/  fixed_buffer_size ; 
 int /*<<< orphan*/  memset (struct ib_odp_caps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  null_mkey ; 
 int /*<<< orphan*/  pg ; 
 TYPE_3__ rc_odp_caps ; 
 TYPE_2__ ud_odp_caps ; 
 int /*<<< orphan*/  umr_extended_translation_offset ; 

void mlx5_ib_internal_fill_odp_caps(struct mlx5_ib_dev *dev)
{
	struct ib_odp_caps *caps = &dev->odp_caps;

	memset(caps, 0, sizeof(*caps));

	if (!MLX5_CAP_GEN(dev->mdev, pg))
		return;

	caps->general_caps = IB_ODP_SUPPORT;

	if (MLX5_CAP_GEN(dev->mdev, umr_extended_translation_offset))
		dev->odp_max_size = U64_MAX;
	else
		dev->odp_max_size = BIT_ULL(MLX5_MAX_UMR_SHIFT + PAGE_SHIFT);

	if (MLX5_CAP_ODP(dev->mdev, ud_odp_caps.send))
		caps->per_transport_caps.ud_odp_caps |= IB_ODP_SUPPORT_SEND;

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

	if (MLX5_CAP_GEN(dev->mdev, fixed_buffer_size) &&
	    MLX5_CAP_GEN(dev->mdev, null_mkey) &&
	    MLX5_CAP_GEN(dev->mdev, umr_extended_translation_offset))
		caps->general_caps |= IB_ODP_SUPPORT_IMPLICIT;

	return;
}