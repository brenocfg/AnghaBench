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
 int SSB_ADM_NEG ; 
 int SSB_ADM_SZ0 ; 
 int SSB_ADM_SZ0_SHIFT ; 
 int SSB_ADM_SZ1 ; 
 int SSB_ADM_SZ1_SHIFT ; 
 int SSB_ADM_SZ2 ; 
 int SSB_ADM_SZ2_SHIFT ; 
 int SSB_ADM_TYPE ; 
#define  SSB_ADM_TYPE0 130 
#define  SSB_ADM_TYPE1 129 
#define  SSB_ADM_TYPE2 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

u32 ssb_admatch_size(u32 adm)
{
	u32 size = 0;

	switch (adm & SSB_ADM_TYPE) {
	case SSB_ADM_TYPE0:
		size = ((adm & SSB_ADM_SZ0) >> SSB_ADM_SZ0_SHIFT);
		break;
	case SSB_ADM_TYPE1:
		WARN_ON(adm & SSB_ADM_NEG); /* unsupported */
		size = ((adm & SSB_ADM_SZ1) >> SSB_ADM_SZ1_SHIFT);
		break;
	case SSB_ADM_TYPE2:
		WARN_ON(adm & SSB_ADM_NEG); /* unsupported */
		size = ((adm & SSB_ADM_SZ2) >> SSB_ADM_SZ2_SHIFT);
		break;
	default:
		WARN_ON(1);
	}
	size = (1 << (size + 1));

	return size;
}