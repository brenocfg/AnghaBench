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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct ib_wc {int /*<<< orphan*/  slid; } ;
struct TYPE_2__ {scalar_t__ method; scalar_t__ mgmt_class; scalar_t__ attr_id; int /*<<< orphan*/  status; } ;
struct ib_mad {TYPE_1__ mad_hdr; } ;
struct ib_grh {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_LID_PERMISSIVE ; 
 int IB_MAD_IGNORE_BKEY ; 
 int IB_MAD_IGNORE_MKEY ; 
 int IB_MAD_RESULT_CONSUMED ; 
 int IB_MAD_RESULT_FAILURE ; 
 int IB_MAD_RESULT_REPLY ; 
 int IB_MAD_RESULT_SUCCESS ; 
 scalar_t__ IB_MGMT_CLASS_CONG_MGMT ; 
 scalar_t__ IB_MGMT_CLASS_PERF_MGMT ; 
 scalar_t__ IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE ; 
 scalar_t__ IB_MGMT_CLASS_SUBN_LID_ROUTED ; 
 scalar_t__ IB_MGMT_METHOD_GET ; 
 scalar_t__ IB_MGMT_METHOD_SET ; 
 scalar_t__ IB_MGMT_METHOD_TRAP ; 
 scalar_t__ IB_MGMT_METHOD_TRAP_REPRESS ; 
 scalar_t__ IB_SMP_ATTR_SM_INFO ; 
 scalar_t__ MLX5_IB_VENDOR_CLASS1 ; 
 scalar_t__ MLX5_IB_VENDOR_CLASS2 ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 scalar_t__ ib_lid_cpu16 (int /*<<< orphan*/ ) ; 
 int mlx5_MAD_IFC (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct ib_wc const*,struct ib_grh const*,struct ib_mad const*,struct ib_mad*) ; 
 int /*<<< orphan*/  to_mdev (struct ib_device*) ; 

__attribute__((used)) static int process_mad(struct ib_device *ibdev, int mad_flags, u8 port_num,
		       const struct ib_wc *in_wc, const struct ib_grh *in_grh,
		       const struct ib_mad *in_mad, struct ib_mad *out_mad)
{
	u16 slid;
	int err;

	slid = in_wc ? ib_lid_cpu16(in_wc->slid) : be16_to_cpu(IB_LID_PERMISSIVE);

	if (in_mad->mad_hdr.method == IB_MGMT_METHOD_TRAP && slid == 0)
		return IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;

	if (in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_LID_ROUTED ||
	    in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE) {
		if (in_mad->mad_hdr.method   != IB_MGMT_METHOD_GET &&
		    in_mad->mad_hdr.method   != IB_MGMT_METHOD_SET &&
		    in_mad->mad_hdr.method   != IB_MGMT_METHOD_TRAP_REPRESS)
			return IB_MAD_RESULT_SUCCESS;

		/* Don't process SMInfo queries -- the SMA can't handle them.
		 */
		if (in_mad->mad_hdr.attr_id == IB_SMP_ATTR_SM_INFO)
			return IB_MAD_RESULT_SUCCESS;
	} else if (in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_PERF_MGMT ||
		   in_mad->mad_hdr.mgmt_class == MLX5_IB_VENDOR_CLASS1   ||
		   in_mad->mad_hdr.mgmt_class == MLX5_IB_VENDOR_CLASS2   ||
		   in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_CONG_MGMT) {
		if (in_mad->mad_hdr.method  != IB_MGMT_METHOD_GET &&
		    in_mad->mad_hdr.method  != IB_MGMT_METHOD_SET)
			return IB_MAD_RESULT_SUCCESS;
	} else {
		return IB_MAD_RESULT_SUCCESS;
	}

	err = mlx5_MAD_IFC(to_mdev(ibdev),
			   mad_flags & IB_MAD_IGNORE_MKEY,
			   mad_flags & IB_MAD_IGNORE_BKEY,
			   port_num, in_wc, in_grh, in_mad, out_mad);
	if (err)
		return IB_MAD_RESULT_FAILURE;

	/* set return bit in status of directed route responses */
	if (in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE)
		out_mad->mad_hdr.status |= cpu_to_be16(1 << 15);

	if (in_mad->mad_hdr.method == IB_MGMT_METHOD_TRAP_REPRESS)
		/* no response for trap repress */
		return IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;

	return IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY;
}