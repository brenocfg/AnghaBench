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
struct cxl_process_element_hcall {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_H_WAIT_UNTIL_DONE (long,unsigned long*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 long EBUSY ; 
 long EINVAL ; 
 int /*<<< orphan*/  H_ATTACH_CA_PROCESS ; 
#define  H_AUTHORITY 135 
#define  H_BUSY 134 
#define  H_FUNCTION 133 
#define  H_HARDWARE 132 
#define  H_PARAMETER 131 
#define  H_RESOURCE 130 
#define  H_STATE 129 
#define  H_SUCCESS 128 
 int PLPAR_HCALL_BUFSIZE ; 
 int /*<<< orphan*/  WARN (int,char*,long) ; 
 int /*<<< orphan*/  _PRINT_MSG (long,char*,unsigned long,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  cxl_dump_debug_buffer (struct cxl_process_element_hcall*,int) ; 
 int /*<<< orphan*/  pr_devel (char*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  trace_cxl_hcall_attach (unsigned long,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,long) ; 
 int /*<<< orphan*/  virt_to_phys (struct cxl_process_element_hcall*) ; 

long cxl_h_attach_process(u64 unit_address,
			struct cxl_process_element_hcall *element,
			u64 *process_token, u64 *mmio_addr, u64 *mmio_size)
{
	unsigned long retbuf[PLPAR_HCALL_BUFSIZE];
	long rc;

	CXL_H_WAIT_UNTIL_DONE(rc, retbuf, H_ATTACH_CA_PROCESS, unit_address, virt_to_phys(element));
	_PRINT_MSG(rc, "cxl_h_attach_process(%#.16llx, %#.16lx): %li\n",
		unit_address, virt_to_phys(element), rc);
	trace_cxl_hcall_attach(unit_address, virt_to_phys(element), retbuf[0], retbuf[1], retbuf[2], rc);

	pr_devel("token: 0x%.8lx mmio_addr: 0x%lx mmio_size: 0x%lx\nProcess Element Structure:\n",
		retbuf[0], retbuf[1], retbuf[2]);
	cxl_dump_debug_buffer(element, sizeof(*element));

	switch (rc) {
	case H_SUCCESS:       /* The process info is attached to the coherent platform function */
		*process_token = retbuf[0];
		if (mmio_addr)
			*mmio_addr = retbuf[1];
		if (mmio_size)
			*mmio_size = retbuf[2];
		return 0;
	case H_PARAMETER:     /* An incorrect parameter was supplied. */
	case H_FUNCTION:      /* The function is not supported. */
		return -EINVAL;
	case H_AUTHORITY:     /* The partition does not have authority to perform this hcall */
	case H_RESOURCE:      /* The coherent platform function does not have enough additional resource to attach the process */
	case H_HARDWARE:      /* A hardware event prevented the attach operation */
	case H_STATE:         /* The coherent platform function is not in a valid state */
	case H_BUSY:
		return -EBUSY;
	default:
		WARN(1, "Unexpected return code: %lx", rc);
		return -EINVAL;
	}
}