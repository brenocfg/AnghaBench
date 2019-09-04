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
typedef  int /*<<< orphan*/  retbuf ;

/* Variables and functions */
 long EBUSY ; 
 long EINVAL ; 
#define  H_AUTHORITY 134 
 int /*<<< orphan*/  H_CONTROL_CA_FAULTS ; 
 int /*<<< orphan*/  H_CONTROL_CA_FAULTS_RESPOND_PSL ; 
#define  H_FUNCTION 133 
#define  H_HARDWARE 132 
#define  H_NOT_FOUND 131 
#define  H_PARAMETER 130 
#define  H_STATE 129 
#define  H_SUCCESS 128 
 int PLPAR_HCALL_BUFSIZE ; 
 int /*<<< orphan*/  WARN (int,char*,long) ; 
 int /*<<< orphan*/  _PRINT_MSG (long,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,unsigned long) ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,int) ; 
 long plpar_hcall (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_cxl_hcall_control_faults (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,long) ; 

long cxl_h_control_faults(u64 unit_address, u64 process_token,
			  u64 control_mask, u64 reset_mask)
{
	unsigned long retbuf[PLPAR_HCALL_BUFSIZE];
	long rc;

	memset(retbuf, 0, sizeof(retbuf));

	rc = plpar_hcall(H_CONTROL_CA_FAULTS, retbuf, unit_address,
			H_CONTROL_CA_FAULTS_RESPOND_PSL, process_token,
			control_mask, reset_mask);
	_PRINT_MSG(rc, "cxl_h_control_faults(%#.16llx, 0x%llx, %#llx, %#llx): %li (%#lx)\n",
		unit_address, process_token, control_mask, reset_mask,
		rc, retbuf[0]);
	trace_cxl_hcall_control_faults(unit_address, process_token,
				control_mask, reset_mask, retbuf[0], rc);

	switch (rc) {
	case H_SUCCESS:    /* Faults were successfully controlled for the function. */
		return 0;
	case H_PARAMETER:  /* An incorrect parameter was supplied. */
		return -EINVAL;
	case H_HARDWARE:   /* A hardware event prevented the control of faults. */
	case H_STATE:      /* The function was in an invalid state. */
	case H_AUTHORITY:  /* The partition does not have authority to perform this hcall; the coherent platform facilities may need to be licensed. */
		return -EBUSY;
	case H_FUNCTION:   /* The function is not supported */
	case H_NOT_FOUND:  /* The operation supplied was not valid */
		return -EINVAL;
	default:
		WARN(1, "Unexpected return code: %lx", rc);
		return -EINVAL;
	}
}