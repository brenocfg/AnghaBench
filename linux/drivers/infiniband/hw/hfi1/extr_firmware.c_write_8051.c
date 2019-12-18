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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int DC8051_ACCESS_TIMEOUT ; 
 int /*<<< orphan*/  DC_DC8051_CFG_RAM_ACCESS_CTRL ; 
 int DC_DC8051_CFG_RAM_ACCESS_CTRL_ADDRESS_MASK ; 
 int DC_DC8051_CFG_RAM_ACCESS_CTRL_ADDRESS_SHIFT ; 
 int DC_DC8051_CFG_RAM_ACCESS_CTRL_WRITE_ENA_SMASK ; 
 int /*<<< orphan*/  DC_DC8051_CFG_RAM_ACCESS_SETUP ; 
 unsigned long long DC_DC8051_CFG_RAM_ACCESS_SETUP_AUTO_INCR_ADDR_SMASK ; 
 unsigned long long DC_DC8051_CFG_RAM_ACCESS_SETUP_RAM_SEL_SMASK ; 
 int /*<<< orphan*/  DC_DC8051_CFG_RAM_ACCESS_STATUS ; 
 int DC_DC8051_CFG_RAM_ACCESS_STATUS_ACCESS_COMPLETED_SMASK ; 
 int /*<<< orphan*/  DC_DC8051_CFG_RAM_ACCESS_WR_DATA ; 
 int ENXIO ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,int) ; 
 int read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int write_8051(struct hfi1_devdata *dd, int code, u32 start,
		      const u8 *data, u32 len)
{
	u64 reg;
	u32 offset;
	int aligned, count;

	/* check alignment */
	aligned = ((unsigned long)data & 0x7) == 0;

	/* write set-up */
	reg = (code ? DC_DC8051_CFG_RAM_ACCESS_SETUP_RAM_SEL_SMASK : 0ull)
		| DC_DC8051_CFG_RAM_ACCESS_SETUP_AUTO_INCR_ADDR_SMASK;
	write_csr(dd, DC_DC8051_CFG_RAM_ACCESS_SETUP, reg);

	reg = ((start & DC_DC8051_CFG_RAM_ACCESS_CTRL_ADDRESS_MASK)
			<< DC_DC8051_CFG_RAM_ACCESS_CTRL_ADDRESS_SHIFT)
		| DC_DC8051_CFG_RAM_ACCESS_CTRL_WRITE_ENA_SMASK;
	write_csr(dd, DC_DC8051_CFG_RAM_ACCESS_CTRL, reg);

	/* write */
	for (offset = 0; offset < len; offset += 8) {
		int bytes = len - offset;

		if (bytes < 8) {
			reg = 0;
			memcpy(&reg, &data[offset], bytes);
		} else if (aligned) {
			reg = *(u64 *)&data[offset];
		} else {
			memcpy(&reg, &data[offset], 8);
		}
		write_csr(dd, DC_DC8051_CFG_RAM_ACCESS_WR_DATA, reg);

		/* wait until ACCESS_COMPLETED is set */
		count = 0;
		while ((read_csr(dd, DC_DC8051_CFG_RAM_ACCESS_STATUS)
		    & DC_DC8051_CFG_RAM_ACCESS_STATUS_ACCESS_COMPLETED_SMASK)
		    == 0) {
			count++;
			if (count > DC8051_ACCESS_TIMEOUT) {
				dd_dev_err(dd, "timeout writing 8051 data\n");
				return -ENXIO;
			}
			udelay(1);
		}
	}

	/* turn off write access, auto increment (also sets to data access) */
	write_csr(dd, DC_DC8051_CFG_RAM_ACCESS_CTRL, 0);
	write_csr(dd, DC_DC8051_CFG_RAM_ACCESS_SETUP, 0);

	return 0;
}