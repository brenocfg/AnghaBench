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
typedef  unsigned long u64 ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_H9_WAIT_UNTIL_DONE (long,unsigned long*,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 long EBUSY ; 
 long EINVAL ; 
#define  H_AUTHORITY 138 
#define  H_BUSY 137 
 int /*<<< orphan*/  H_CONTROL_CA_FACILITY ; 
 unsigned long H_CONTROL_CA_FACILITY_COLLECT_VPD ; 
#define  H_FUNCTION 136 
#define  H_HARDWARE 135 
#define  H_NOT_AVAILABLE 134 
#define  H_NOT_FOUND 133 
#define  H_PARAMETER 132 
#define  H_RESOURCE 131 
#define  H_SG_LIST 130 
#define  H_STATE 129 
#define  H_SUCCESS 128 
 int /*<<< orphan*/  OP_STR_CONTROL_ADAPTER (unsigned long) ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 int /*<<< orphan*/  WARN (int,char*,long) ; 
 int /*<<< orphan*/  _PRINT_MSG (long,char*,unsigned long,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,long) ; 
 int /*<<< orphan*/  trace_cxl_hcall_control_facility (unsigned long,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,long) ; 

__attribute__((used)) static long cxl_h_control_facility(u64 unit_address, u64 op,
				   u64 p1, u64 p2, u64 p3, u64 p4, u64 *out)
{
	unsigned long retbuf[PLPAR_HCALL9_BUFSIZE];
	long rc;

	CXL_H9_WAIT_UNTIL_DONE(rc, retbuf, H_CONTROL_CA_FACILITY, unit_address, op, p1, p2, p3, p4);
	_PRINT_MSG(rc, "cxl_h_control_facility(%#.16llx, %s(%#llx, %#llx, %#llx, %#llx, R4: %#lx)): %li\n",
		unit_address, OP_STR_CONTROL_ADAPTER(op), p1, p2, p3, p4, retbuf[0], rc);
	trace_cxl_hcall_control_facility(unit_address, OP_STR_CONTROL_ADAPTER(op), p1, p2, p3, p4, retbuf[0], rc);

	switch (rc) {
	case H_SUCCESS:       /* The operation is completed for the coherent platform facility */
		if (op == H_CONTROL_CA_FACILITY_COLLECT_VPD)
			*out = retbuf[0];
		return 0;
	case H_PARAMETER:     /* An incorrect parameter was supplied. */
	case H_FUNCTION:      /* The function is not supported. */
	case H_NOT_FOUND:     /* The operation supplied was not valid */
	case H_NOT_AVAILABLE: /* The operation cannot be performed because the AFU has not been downloaded */
	case H_SG_LIST:       /* An block list entry was invalid */
		return -EINVAL;
	case H_AUTHORITY:     /* The partition does not have authority to perform this hcall */
	case H_RESOURCE:      /* The function has page table mappings for MMIO */
	case H_HARDWARE:      /* A hardware event prevented the attach operation */
	case H_STATE:         /* The coherent platform facility is not in a valid state */
	case H_BUSY:
		return -EBUSY;
	default:
		WARN(1, "Unexpected return code: %lx", rc);
		return -EINVAL;
	}
}