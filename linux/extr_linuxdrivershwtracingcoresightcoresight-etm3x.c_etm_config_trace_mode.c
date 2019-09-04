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
typedef  int u32 ;
struct etm_config {int mode; int enable_ctrl2; int* addr_val; int* addr_acctype; void** addr_type; int /*<<< orphan*/  enable_ctrl1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETMTECR1_ADDR_COMP_1 ; 
 void* ETM_ADDR_TYPE_RANGE ; 
 int ETM_MODE_EXCL_KERN ; 
 int ETM_MODE_EXCL_USER ; 

void etm_config_trace_mode(struct etm_config *config)
{
	u32 flags, mode;

	mode = config->mode;

	mode &= (ETM_MODE_EXCL_KERN | ETM_MODE_EXCL_USER);

	/* excluding kernel AND user space doesn't make sense */
	if (mode == (ETM_MODE_EXCL_KERN | ETM_MODE_EXCL_USER))
		return;

	/* nothing to do if neither flags are set */
	if (!(mode & ETM_MODE_EXCL_KERN) && !(mode & ETM_MODE_EXCL_USER))
		return;

	flags = (1 << 0 |	/* instruction execute */
		 3 << 3 |	/* ARM instruction */
		 0 << 5 |	/* No data value comparison */
		 0 << 7 |	/* No exact mach */
		 0 << 8);	/* Ignore context ID */

	/* No need to worry about single address comparators. */
	config->enable_ctrl2 = 0x0;

	/* Bit 0 is address range comparator 1 */
	config->enable_ctrl1 = ETMTECR1_ADDR_COMP_1;

	/*
	 * On ETMv3.5:
	 * ETMACTRn[13,11] == Non-secure state comparison control
	 * ETMACTRn[12,10] == Secure state comparison control
	 *
	 * b00 == Match in all modes in this state
	 * b01 == Do not match in any more in this state
	 * b10 == Match in all modes excepts user mode in this state
	 * b11 == Match only in user mode in this state
	 */

	/* Tracing in secure mode is not supported at this time */
	flags |= (0 << 12 | 1 << 10);

	if (mode & ETM_MODE_EXCL_USER) {
		/* exclude user, match all modes except user mode */
		flags |= (1 << 13 | 0 << 11);
	} else {
		/* exclude kernel, match only in user mode */
		flags |= (1 << 13 | 1 << 11);
	}

	/*
	 * The ETMEEVR register is already set to "hard wire A".  As such
	 * all there is to do is setup an address comparator that spans
	 * the entire address range and configure the state and mode bits.
	 */
	config->addr_val[0] = (u32) 0x0;
	config->addr_val[1] = (u32) ~0x0;
	config->addr_acctype[0] = flags;
	config->addr_acctype[1] = flags;
	config->addr_type[0] = ETM_ADDR_TYPE_RANGE;
	config->addr_type[1] = ETM_ADDR_TYPE_RANGE;
}