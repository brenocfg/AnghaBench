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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_H_WAIT_UNTIL_DONE (long,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long EBUSY ; 
 long EINVAL ; 
#define  H_AUTHORITY 134 
#define  H_BUSY 133 
 int /*<<< orphan*/  H_DETACH_CA_PROCESS ; 
#define  H_HARDWARE 132 
#define  H_PARAMETER 131 
#define  H_RESOURCE 130 
#define  H_STATE 129 
#define  H_SUCCESS 128 
 int PLPAR_HCALL_BUFSIZE ; 
 int /*<<< orphan*/  WARN (int,char*,long) ; 
 int /*<<< orphan*/  _PRINT_MSG (long,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  trace_cxl_hcall_detach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

long cxl_h_detach_process(u64 unit_address, u64 process_token)
{
	unsigned long retbuf[PLPAR_HCALL_BUFSIZE];
	long rc;

	CXL_H_WAIT_UNTIL_DONE(rc, retbuf, H_DETACH_CA_PROCESS, unit_address, process_token);
	_PRINT_MSG(rc, "cxl_h_detach_process(%#.16llx, 0x%.8llx): %li\n", unit_address, process_token, rc);
	trace_cxl_hcall_detach(unit_address, process_token, rc);

	switch (rc) {
	case H_SUCCESS:       /* The process was detached from the coherent platform function */
		return 0;
	case H_PARAMETER:     /* An incorrect parameter was supplied. */
		return -EINVAL;
	case H_AUTHORITY:     /* The partition does not have authority to perform this hcall */
	case H_RESOURCE:      /* The function has page table mappings for MMIO */
	case H_HARDWARE:      /* A hardware event prevented the detach operation */
	case H_STATE:         /* The coherent platform function is not in a valid state */
	case H_BUSY:
		return -EBUSY;
	default:
		WARN(1, "Unexpected return code: %lx", rc);
		return -EINVAL;
	}
}