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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct qedr_dev {int dummy; } ;
struct ib_wc {int dummy; } ;
struct ib_mad_hdr {int /*<<< orphan*/  status; int /*<<< orphan*/  mgmt_class; int /*<<< orphan*/  method; int /*<<< orphan*/  class_version; int /*<<< orphan*/  class_specific; int /*<<< orphan*/  attr_mod; int /*<<< orphan*/  base_version; int /*<<< orphan*/  attr_id; } ;
struct ib_grh {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IB_MAD_RESULT_SUCCESS ; 
 int /*<<< orphan*/  QEDR_MSG_GSI ; 
 struct qedr_dev* get_qedr_dev (struct ib_device*) ; 

int qedr_process_mad(struct ib_device *ibdev, int process_mad_flags,
		     u8 port_num,
		     const struct ib_wc *in_wc,
		     const struct ib_grh *in_grh,
		     const struct ib_mad_hdr *mad_hdr,
		     size_t in_mad_size, struct ib_mad_hdr *out_mad,
		     size_t *out_mad_size, u16 *out_mad_pkey_index)
{
	struct qedr_dev *dev = get_qedr_dev(ibdev);

	DP_DEBUG(dev, QEDR_MSG_GSI,
		 "QEDR_PROCESS_MAD in_mad %x %x %x %x %x %x %x %x\n",
		 mad_hdr->attr_id, mad_hdr->base_version, mad_hdr->attr_mod,
		 mad_hdr->class_specific, mad_hdr->class_version,
		 mad_hdr->method, mad_hdr->mgmt_class, mad_hdr->status);
	return IB_MAD_RESULT_SUCCESS;
}