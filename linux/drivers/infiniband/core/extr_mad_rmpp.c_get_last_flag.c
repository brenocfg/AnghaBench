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
struct ib_rmpp_mad {int /*<<< orphan*/  rmpp_hdr; } ;
struct ib_mad_recv_buf {scalar_t__ mad; } ;

/* Variables and functions */
 int IB_MGMT_RMPP_FLAG_LAST ; 
 int ib_get_rmpp_flags (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int get_last_flag(struct ib_mad_recv_buf *seg)
{
	struct ib_rmpp_mad *rmpp_mad;

	rmpp_mad = (struct ib_rmpp_mad *) seg->mad;
	return ib_get_rmpp_flags(&rmpp_mad->rmpp_hdr) & IB_MGMT_RMPP_FLAG_LAST;
}