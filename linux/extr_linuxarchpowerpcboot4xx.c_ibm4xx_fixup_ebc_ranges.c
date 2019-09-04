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

/* Variables and functions */
 int /*<<< orphan*/  DCRN_EBC0_CFGADDR ; 
 int /*<<< orphan*/  DCRN_EBC0_CFGDATA ; 
 int /*<<< orphan*/  EBC_BXCR (int) ; 
 int /*<<< orphan*/  EBC_BXCR_BANK_SIZE (int) ; 
 int EBC_BXCR_BAS ; 
 int EBC_BXCR_BU ; 
 int EBC_BXCR_BU_OFF ; 
 int EBC_NUM_BANKS ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 void* finddevice (char const*) ; 
 int mfdcr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtdcr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setprop (void*,char*,int*,int) ; 

void ibm4xx_fixup_ebc_ranges(const char *ebc)
{
	void *devp;
	u32 bxcr;
	u32 ranges[EBC_NUM_BANKS*4];
	u32 *p = ranges;
	int i;

	for (i = 0; i < EBC_NUM_BANKS; i++) {
		mtdcr(DCRN_EBC0_CFGADDR, EBC_BXCR(i));
		bxcr = mfdcr(DCRN_EBC0_CFGDATA);

		if ((bxcr & EBC_BXCR_BU) != EBC_BXCR_BU_OFF) {
			*p++ = i;
			*p++ = 0;
			*p++ = bxcr & EBC_BXCR_BAS;
			*p++ = EBC_BXCR_BANK_SIZE(bxcr);
		}
	}

	devp = finddevice(ebc);
	if (! devp)
		fatal("Couldn't locate EBC node %s\n\r", ebc);

	setprop(devp, "ranges", ranges, (p - ranges) * sizeof(u32));
}