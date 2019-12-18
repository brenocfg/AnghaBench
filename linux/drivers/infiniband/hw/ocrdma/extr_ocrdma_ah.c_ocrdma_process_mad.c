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
typedef  int /*<<< orphan*/  u16 ;
struct ocrdma_dev {int dummy; } ;
struct ib_wc {int dummy; } ;
struct ib_mad_hdr {int dummy; } ;
struct TYPE_2__ {int mgmt_class; } ;
struct ib_mad {TYPE_1__ mad_hdr; } ;
struct ib_grh {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int IB_MAD_RESULT_FAILURE ; 
 int IB_MAD_RESULT_REPLY ; 
 int IB_MAD_RESULT_SUCCESS ; 
#define  IB_MGMT_CLASS_PERF_MGMT 128 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct ocrdma_dev* get_ocrdma_dev (struct ib_device*) ; 
 int /*<<< orphan*/  ocrdma_pma_counters (struct ocrdma_dev*,struct ib_mad*) ; 

int ocrdma_process_mad(struct ib_device *ibdev,
		       int process_mad_flags,
		       u8 port_num,
		       const struct ib_wc *in_wc,
		       const struct ib_grh *in_grh,
		       const struct ib_mad_hdr *in, size_t in_mad_size,
		       struct ib_mad_hdr *out, size_t *out_mad_size,
		       u16 *out_mad_pkey_index)
{
	int status;
	struct ocrdma_dev *dev;
	const struct ib_mad *in_mad = (const struct ib_mad *)in;
	struct ib_mad *out_mad = (struct ib_mad *)out;

	if (WARN_ON_ONCE(in_mad_size != sizeof(*in_mad) ||
			 *out_mad_size != sizeof(*out_mad)))
		return IB_MAD_RESULT_FAILURE;

	switch (in_mad->mad_hdr.mgmt_class) {
	case IB_MGMT_CLASS_PERF_MGMT:
		dev = get_ocrdma_dev(ibdev);
		if (!ocrdma_pma_counters(dev, out_mad))
			status = IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY;
		else
			status = IB_MAD_RESULT_SUCCESS;
		break;
	default:
		status = IB_MAD_RESULT_SUCCESS;
		break;
	}
	return status;
}