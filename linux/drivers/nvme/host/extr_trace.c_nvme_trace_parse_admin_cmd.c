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
typedef  int u8 ;
struct trace_seq {int dummy; } ;

/* Variables and functions */
#define  nvme_admin_create_cq 134 
#define  nvme_admin_create_sq 133 
#define  nvme_admin_delete_cq 132 
#define  nvme_admin_delete_sq 131 
#define  nvme_admin_get_features 130 
#define  nvme_admin_get_lba_status 129 
#define  nvme_admin_identify 128 
 char const* nvme_trace_admin_get_features (struct trace_seq*,int*) ; 
 char const* nvme_trace_admin_identify (struct trace_seq*,int*) ; 
 char const* nvme_trace_common (struct trace_seq*,int*) ; 
 char const* nvme_trace_create_cq (struct trace_seq*,int*) ; 
 char const* nvme_trace_create_sq (struct trace_seq*,int*) ; 
 char const* nvme_trace_delete_cq (struct trace_seq*,int*) ; 
 char const* nvme_trace_delete_sq (struct trace_seq*,int*) ; 
 char const* nvme_trace_get_lba_status (struct trace_seq*,int*) ; 

const char *nvme_trace_parse_admin_cmd(struct trace_seq *p,
				       u8 opcode, u8 *cdw10)
{
	switch (opcode) {
	case nvme_admin_delete_sq:
		return nvme_trace_delete_sq(p, cdw10);
	case nvme_admin_create_sq:
		return nvme_trace_create_sq(p, cdw10);
	case nvme_admin_delete_cq:
		return nvme_trace_delete_cq(p, cdw10);
	case nvme_admin_create_cq:
		return nvme_trace_create_cq(p, cdw10);
	case nvme_admin_identify:
		return nvme_trace_admin_identify(p, cdw10);
	case nvme_admin_get_features:
		return nvme_trace_admin_get_features(p, cdw10);
	case nvme_admin_get_lba_status:
		return nvme_trace_get_lba_status(p, cdw10);
	default:
		return nvme_trace_common(p, cdw10);
	}
}