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
#define  nvme_cmd_dsm 131 
#define  nvme_cmd_read 130 
#define  nvme_cmd_write 129 
#define  nvme_cmd_write_zeroes 128 
 char const* nvmet_trace_common (struct trace_seq*,int*) ; 
 char const* nvmet_trace_dsm (struct trace_seq*,int*) ; 
 char const* nvmet_trace_read_write (struct trace_seq*,int*) ; 

const char *nvmet_trace_parse_nvm_cmd(struct trace_seq *p,
		u8 opcode, u8 *cdw10)
{
	switch (opcode) {
	case nvme_cmd_read:
	case nvme_cmd_write:
	case nvme_cmd_write_zeroes:
		return nvmet_trace_read_write(p, cdw10);
	case nvme_cmd_dsm:
		return nvmet_trace_dsm(p, cdw10);
	default:
		return nvmet_trace_common(p, cdw10);
	}
}