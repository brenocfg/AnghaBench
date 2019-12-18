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
typedef  int u64 ;
typedef  int u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int DC8051_ACCESS_TIMEOUT ; 
 int /*<<< orphan*/  DC_DC8051_CFG_RAM_ACCESS_CTRL ; 
 int DC_DC8051_CFG_RAM_ACCESS_CTRL_ADDRESS_MASK ; 
 int DC_DC8051_CFG_RAM_ACCESS_CTRL_ADDRESS_SHIFT ; 
 int DC_DC8051_CFG_RAM_ACCESS_CTRL_READ_ENA_SMASK ; 
 int /*<<< orphan*/  DC_DC8051_CFG_RAM_ACCESS_RD_DATA ; 
 int /*<<< orphan*/  DC_DC8051_CFG_RAM_ACCESS_STATUS ; 
 int DC_DC8051_CFG_RAM_ACCESS_STATUS_ACCESS_COMPLETED_SMASK ; 
 int ENXIO ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __read_8051_data(struct hfi1_devdata *dd, u32 addr, u64 *result)
{
	u64 reg;
	int count;

	/* step 1: set the address, clear enable */
	reg = (addr & DC_DC8051_CFG_RAM_ACCESS_CTRL_ADDRESS_MASK)
			<< DC_DC8051_CFG_RAM_ACCESS_CTRL_ADDRESS_SHIFT;
	write_csr(dd, DC_DC8051_CFG_RAM_ACCESS_CTRL, reg);
	/* step 2: enable */
	write_csr(dd, DC_DC8051_CFG_RAM_ACCESS_CTRL,
		  reg | DC_DC8051_CFG_RAM_ACCESS_CTRL_READ_ENA_SMASK);

	/* wait until ACCESS_COMPLETED is set */
	count = 0;
	while ((read_csr(dd, DC_DC8051_CFG_RAM_ACCESS_STATUS)
		    & DC_DC8051_CFG_RAM_ACCESS_STATUS_ACCESS_COMPLETED_SMASK)
		    == 0) {
		count++;
		if (count > DC8051_ACCESS_TIMEOUT) {
			dd_dev_err(dd, "timeout reading 8051 data\n");
			return -ENXIO;
		}
		ndelay(10);
	}

	/* gather the data */
	*result = read_csr(dd, DC_DC8051_CFG_RAM_ACCESS_RD_DATA);

	return 0;
}