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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  retbuf ;

/* Variables and functions */
 unsigned int CXL_HCALL_TIMEOUT_DOWNLOAD ; 
 long EBUSY ; 
 long EINVAL ; 
#define  H_AUTHORITY 138 
#define  H_BAD_DATA 137 
#define  H_BUSY 136 
#define  H_CONTINUE 135 
 int /*<<< orphan*/  H_DOWNLOAD_CA_FACILITY ; 
#define  H_FUNCTION 134 
#define  H_HARDWARE 133 
 int /*<<< orphan*/  H_IS_LONG_BUSY (long) ; 
#define  H_PARAMETER 132 
#define  H_RESOURCE 131 
#define  H_SG_LIST 130 
#define  H_STATE 129 
#define  H_SUCCESS 128 
 int /*<<< orphan*/  OP_STR_DOWNLOAD_ADAPTER (scalar_t__) ; 
 int PLPAR_HCALL_BUFSIZE ; 
 int /*<<< orphan*/  WARN (int,char*,long,...) ; 
 int /*<<< orphan*/  _PRINT_MSG (long,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,unsigned long,long) ; 
 unsigned int get_longbusy_msecs (long) ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 
 long plpar_hcall (int /*<<< orphan*/ ,unsigned long*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_cxl_hcall_download_facility (scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,unsigned long,long) ; 

__attribute__((used)) static long cxl_h_download_facility(u64 unit_address, u64 op,
				    u64 list_address, u64 num,
				    u64 *out)
{
	unsigned long retbuf[PLPAR_HCALL_BUFSIZE];
	unsigned int delay, total_delay = 0;
	u64 token = 0;
	long rc;

	if (*out != 0)
		token = *out;

	memset(retbuf, 0, sizeof(retbuf));
	while (1) {
		rc = plpar_hcall(H_DOWNLOAD_CA_FACILITY, retbuf,
				 unit_address, op, list_address, num,
				 token);
		token = retbuf[0];
		if (rc != H_BUSY && !H_IS_LONG_BUSY(rc))
			break;

		if (rc != H_BUSY) {
			delay = get_longbusy_msecs(rc);
			total_delay += delay;
			if (total_delay > CXL_HCALL_TIMEOUT_DOWNLOAD) {
				WARN(1, "Warning: Giving up waiting for CXL hcall "
					"%#x after %u msec\n",
					H_DOWNLOAD_CA_FACILITY, total_delay);
				rc = H_BUSY;
				break;
			}
			msleep(delay);
		}
	}
	_PRINT_MSG(rc, "cxl_h_download_facility(%#.16llx, %s(%#llx, %#llx), %#lx): %li\n",
		 unit_address, OP_STR_DOWNLOAD_ADAPTER(op), list_address, num, retbuf[0], rc);
	trace_cxl_hcall_download_facility(unit_address, OP_STR_DOWNLOAD_ADAPTER(op), list_address, num, retbuf[0], rc);

	switch (rc) {
	case H_SUCCESS:       /* The operation is completed for the coherent platform facility */
		return 0;
	case H_PARAMETER:     /* An incorrect parameter was supplied */
	case H_FUNCTION:      /* The function is not supported. */
	case H_SG_LIST:       /* An block list entry was invalid */
	case H_BAD_DATA:      /* Image verification failed */
		return -EINVAL;
	case H_AUTHORITY:     /* The partition does not have authority to perform this hcall */
	case H_RESOURCE:      /* The function has page table mappings for MMIO */
	case H_HARDWARE:      /* A hardware event prevented the attach operation */
	case H_STATE:         /* The coherent platform facility is not in a valid state */
	case H_BUSY:
		return -EBUSY;
	case H_CONTINUE:
		*out = retbuf[0];
		return 1;  /* More data is needed for the complete image */
	default:
		WARN(1, "Unexpected return code: %lx", rc);
		return -EINVAL;
	}
}