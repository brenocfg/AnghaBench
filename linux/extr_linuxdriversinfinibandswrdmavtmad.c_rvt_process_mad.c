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
struct ib_wc {int dummy; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_grh {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_MAD_RESULT_FAILURE ; 
 scalar_t__ ibport_num_to_idx (struct ib_device*,int /*<<< orphan*/ ) ; 

int rvt_process_mad(struct ib_device *ibdev, int mad_flags, u8 port_num,
		    const struct ib_wc *in_wc, const struct ib_grh *in_grh,
		    const struct ib_mad_hdr *in, size_t in_mad_size,
		    struct ib_mad_hdr *out, size_t *out_mad_size,
		    u16 *out_mad_pkey_index)
{
	/*
	 * MAD processing is quite different between hfi1 and qib. Therefore
	 * this is expected to be provided by the driver. Other drivers in the
	 * future may choose to implement this but it should not be made into a
	 * requirement.
	 */
	if (ibport_num_to_idx(ibdev, port_num) < 0)
		return -EINVAL;

	return IB_MAD_RESULT_FAILURE;
}