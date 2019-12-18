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
typedef  int u32 ;
struct hfi1_devdata {scalar_t__ icode; } ;

/* Variables and functions */
 int DC_LCB_CFG_RUN ; 
 int EBUSY ; 
 int /*<<< orphan*/  HCMD_READ_LCB_CSR ; 
 int HCMD_SUCCESS ; 
 scalar_t__ ICODE_FUNCTIONAL_SIMULATOR ; 
 scalar_t__ acquire_lcb_access (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int do_8051_command (struct hfi1_devdata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_csr (struct hfi1_devdata*,int) ; 
 int /*<<< orphan*/  release_lcb_access (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_lcb_via_8051(struct hfi1_devdata *dd, u32 addr, u64 *data)
{
	u32 regno;
	int ret;

	if (dd->icode == ICODE_FUNCTIONAL_SIMULATOR) {
		if (acquire_lcb_access(dd, 0) == 0) {
			*data = read_csr(dd, addr);
			release_lcb_access(dd, 0);
			return 0;
		}
		return -EBUSY;
	}

	/* register is an index of LCB registers: (offset - base) / 8 */
	regno = (addr - DC_LCB_CFG_RUN) >> 3;
	ret = do_8051_command(dd, HCMD_READ_LCB_CSR, regno, data);
	if (ret != HCMD_SUCCESS)
		return -EBUSY;
	return 0;
}