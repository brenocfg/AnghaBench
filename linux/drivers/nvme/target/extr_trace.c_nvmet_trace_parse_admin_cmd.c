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
#define  nvme_admin_get_features 130 
#define  nvme_admin_get_lba_status 129 
#define  nvme_admin_identify 128 
 char const* nvmet_trace_admin_get_features (struct trace_seq*,int*) ; 
 char const* nvmet_trace_admin_identify (struct trace_seq*,int*) ; 
 char const* nvmet_trace_common (struct trace_seq*,int*) ; 
 char const* nvmet_trace_get_lba_status (struct trace_seq*,int*) ; 

const char *nvmet_trace_parse_admin_cmd(struct trace_seq *p,
		u8 opcode, u8 *cdw10)
{
	switch (opcode) {
	case nvme_admin_identify:
		return nvmet_trace_admin_identify(p, cdw10);
	case nvme_admin_get_features:
		return nvmet_trace_admin_get_features(p, cdw10);
	case nvme_admin_get_lba_status:
		return nvmet_trace_get_lba_status(p, cdw10);
	default:
		return nvmet_trace_common(p, cdw10);
	}
}