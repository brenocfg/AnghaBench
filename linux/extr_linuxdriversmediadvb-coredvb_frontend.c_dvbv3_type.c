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
typedef  enum dvbv3_emulation_type { ____Placeholder_dvbv3_emulation_type } dvbv3_emulation_type ;

/* Variables and functions */
 int DVBV3_ATSC ; 
 int DVBV3_OFDM ; 
 int DVBV3_QAM ; 
 int DVBV3_QPSK ; 
 int DVBV3_UNKNOWN ; 
#define  SYS_ATSC 145 
#define  SYS_ATSCMH 144 
#define  SYS_DAB 143 
#define  SYS_DSS 142 
#define  SYS_DTMB 141 
#define  SYS_DVBC_ANNEX_A 140 
#define  SYS_DVBC_ANNEX_B 139 
#define  SYS_DVBC_ANNEX_C 138 
#define  SYS_DVBH 137 
#define  SYS_DVBS 136 
#define  SYS_DVBS2 135 
#define  SYS_DVBT 134 
#define  SYS_DVBT2 133 
#define  SYS_ISDBC 132 
#define  SYS_ISDBS 131 
#define  SYS_ISDBT 130 
#define  SYS_TURBO 129 
#define  SYS_UNDEFINED 128 

__attribute__((used)) static enum dvbv3_emulation_type dvbv3_type(u32 delivery_system)
{
	switch (delivery_system) {
	case SYS_DVBC_ANNEX_A:
	case SYS_DVBC_ANNEX_C:
		return DVBV3_QAM;
	case SYS_DVBS:
	case SYS_DVBS2:
	case SYS_TURBO:
	case SYS_ISDBS:
	case SYS_DSS:
		return DVBV3_QPSK;
	case SYS_DVBT:
	case SYS_DVBT2:
	case SYS_ISDBT:
	case SYS_DTMB:
		return DVBV3_OFDM;
	case SYS_ATSC:
	case SYS_ATSCMH:
	case SYS_DVBC_ANNEX_B:
		return DVBV3_ATSC;
	case SYS_UNDEFINED:
	case SYS_ISDBC:
	case SYS_DVBH:
	case SYS_DAB:
	default:
		/*
		 * Doesn't know how to emulate those types and/or
		 * there's no frontend driver from this type yet
		 * with some emulation code, so, we're not sure yet how
		 * to handle them, or they're not compatible with a DVBv3 call.
		 */
		return DVBV3_UNKNOWN;
	}
}