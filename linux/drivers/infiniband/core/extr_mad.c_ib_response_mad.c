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
struct ib_mad_hdr {int method; scalar_t__ mgmt_class; int attr_mod; } ;

/* Variables and functions */
 int IB_BM_ATTR_MOD_RESP ; 
 scalar_t__ IB_MGMT_CLASS_BM ; 
 int IB_MGMT_METHOD_RESP ; 
 int IB_MGMT_METHOD_TRAP_REPRESS ; 

int ib_response_mad(const struct ib_mad_hdr *hdr)
{
	return ((hdr->method & IB_MGMT_METHOD_RESP) ||
		(hdr->method == IB_MGMT_METHOD_TRAP_REPRESS) ||
		((hdr->mgmt_class == IB_MGMT_CLASS_BM) &&
		 (hdr->attr_mod & IB_BM_ATTR_MOD_RESP)));
}