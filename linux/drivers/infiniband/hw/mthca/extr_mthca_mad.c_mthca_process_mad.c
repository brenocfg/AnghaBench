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
struct ib_port_attr {int /*<<< orphan*/  lid; } ;
struct ib_mad_hdr {int dummy; } ;
struct TYPE_2__ {scalar_t__ method; scalar_t__ mgmt_class; int attr_id; int /*<<< orphan*/  status; } ;
struct ib_mad {TYPE_1__ mad_hdr; } ;
struct ib_grh {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EBADMSG ; 
 int /*<<< orphan*/  IB_LID_PERMISSIVE ; 
 int IB_MAD_IGNORE_BKEY ; 
 int IB_MAD_IGNORE_MKEY ; 
 int IB_MAD_RESULT_CONSUMED ; 
 int IB_MAD_RESULT_FAILURE ; 
 int IB_MAD_RESULT_REPLY ; 
 int IB_MAD_RESULT_SUCCESS ; 
 scalar_t__ IB_MGMT_CLASS_PERF_MGMT ; 
 scalar_t__ IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE ; 
 scalar_t__ IB_MGMT_CLASS_SUBN_LID_ROUTED ; 
 scalar_t__ IB_MGMT_METHOD_GET ; 
 scalar_t__ IB_MGMT_METHOD_SET ; 
 scalar_t__ IB_MGMT_METHOD_TRAP ; 
 scalar_t__ IB_MGMT_METHOD_TRAP_REPRESS ; 
 int IB_SMP_ATTR_PORT_INFO ; 
 int IB_SMP_ATTR_SM_INFO ; 
 int IB_SMP_ATTR_VENDOR_MASK ; 
 scalar_t__ MTHCA_VENDOR_CLASS1 ; 
 scalar_t__ MTHCA_VENDOR_CLASS2 ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  forward_trap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_mad const*) ; 
 scalar_t__ ib_lid_cpu16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_query_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 
 int mthca_MAD_IFC (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct ib_wc const*,struct ib_grh const*,struct ib_mad const*,struct ib_mad*) ; 
 int /*<<< orphan*/  mthca_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  node_desc_override (struct ib_device*,struct ib_mad*) ; 
 int /*<<< orphan*/  smp_snoop (struct ib_device*,int /*<<< orphan*/ ,struct ib_mad const*,scalar_t__) ; 
 int /*<<< orphan*/  to_mdev (struct ib_device*) ; 

int mthca_process_mad(struct ib_device *ibdev,
		      int mad_flags,
		      u8 port_num,
		      const struct ib_wc *in_wc,
		      const struct ib_grh *in_grh,
		      const struct ib_mad_hdr *in, size_t in_mad_size,
		      struct ib_mad_hdr *out, size_t *out_mad_size,
		      u16 *out_mad_pkey_index)
{
	int err;
	u16 slid = in_wc ? ib_lid_cpu16(in_wc->slid) : be16_to_cpu(IB_LID_PERMISSIVE);
	u16 prev_lid = 0;
	struct ib_port_attr pattr;
	const struct ib_mad *in_mad = (const struct ib_mad *)in;
	struct ib_mad *out_mad = (struct ib_mad *)out;

	if (WARN_ON_ONCE(in_mad_size != sizeof(*in_mad) ||
			 *out_mad_size != sizeof(*out_mad)))
		return IB_MAD_RESULT_FAILURE;

	/* Forward locally generated traps to the SM */
	if (in_mad->mad_hdr.method == IB_MGMT_METHOD_TRAP &&
	    slid == 0) {
		forward_trap(to_mdev(ibdev), port_num, in_mad);
		return IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;
	}

	/*
	 * Only handle SM gets, sets and trap represses for SM class
	 *
	 * Only handle PMA and Mellanox vendor-specific class gets and
	 * sets for other classes.
	 */
	if (in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_LID_ROUTED ||
	    in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE) {
		if (in_mad->mad_hdr.method   != IB_MGMT_METHOD_GET &&
		    in_mad->mad_hdr.method   != IB_MGMT_METHOD_SET &&
		    in_mad->mad_hdr.method   != IB_MGMT_METHOD_TRAP_REPRESS)
			return IB_MAD_RESULT_SUCCESS;

		/*
		 * Don't process SMInfo queries or vendor-specific
		 * MADs -- the SMA can't handle them.
		 */
		if (in_mad->mad_hdr.attr_id == IB_SMP_ATTR_SM_INFO ||
		    ((in_mad->mad_hdr.attr_id & IB_SMP_ATTR_VENDOR_MASK) ==
		     IB_SMP_ATTR_VENDOR_MASK))
			return IB_MAD_RESULT_SUCCESS;
	} else if (in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_PERF_MGMT ||
		   in_mad->mad_hdr.mgmt_class == MTHCA_VENDOR_CLASS1     ||
		   in_mad->mad_hdr.mgmt_class == MTHCA_VENDOR_CLASS2) {
		if (in_mad->mad_hdr.method  != IB_MGMT_METHOD_GET &&
		    in_mad->mad_hdr.method  != IB_MGMT_METHOD_SET)
			return IB_MAD_RESULT_SUCCESS;
	} else
		return IB_MAD_RESULT_SUCCESS;
	if ((in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_LID_ROUTED ||
	     in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE) &&
	    in_mad->mad_hdr.method == IB_MGMT_METHOD_SET &&
	    in_mad->mad_hdr.attr_id == IB_SMP_ATTR_PORT_INFO &&
	    !ib_query_port(ibdev, port_num, &pattr))
		prev_lid = ib_lid_cpu16(pattr.lid);

	err = mthca_MAD_IFC(to_mdev(ibdev),
			    mad_flags & IB_MAD_IGNORE_MKEY,
			    mad_flags & IB_MAD_IGNORE_BKEY,
			    port_num, in_wc, in_grh, in_mad, out_mad);
	if (err == -EBADMSG)
		return IB_MAD_RESULT_SUCCESS;
	else if (err) {
		mthca_err(to_mdev(ibdev), "MAD_IFC returned %d\n", err);
		return IB_MAD_RESULT_FAILURE;
	}

	if (!out_mad->mad_hdr.status) {
		smp_snoop(ibdev, port_num, in_mad, prev_lid);
		node_desc_override(ibdev, out_mad);
	}

	/* set return bit in status of directed route responses */
	if (in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE)
		out_mad->mad_hdr.status |= cpu_to_be16(1 << 15);

	if (in_mad->mad_hdr.method == IB_MGMT_METHOD_TRAP_REPRESS)
		/* no response for trap repress */
		return IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;

	return IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY;
}