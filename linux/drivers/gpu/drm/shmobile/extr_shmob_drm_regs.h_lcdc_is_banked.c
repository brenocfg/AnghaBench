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
 int LDBnBBGCL (int /*<<< orphan*/ ) ; 
 int LDBnBPPCR (int) ; 
#define  LDDFR 145 
#define  LDHAJR 144 
#define  LDHCNR 143 
#define  LDHPDR 142 
#define  LDHSYNR 141 
#define  LDMLSR 140 
#define  LDMT1R 139 
#define  LDMT2R 138 
#define  LDMT3R 137 
#define  LDSA1R 136 
#define  LDSA2R 135 
#define  LDSM1R 134 
#define  LDVLNR 133 
#define  LDVPDR 132 
#define  LDVSYNR 131 
#define  LDWBAR 130 
#define  LDWBCNTR 129 
#define  LDWBFR 128 

__attribute__((used)) static inline bool lcdc_is_banked(u32 reg)
{
	switch (reg) {
	case LDMT1R:
	case LDMT2R:
	case LDMT3R:
	case LDDFR:
	case LDSM1R:
	case LDSA1R:
	case LDSA2R:
	case LDMLSR:
	case LDWBFR:
	case LDWBCNTR:
	case LDWBAR:
	case LDHCNR:
	case LDHSYNR:
	case LDVLNR:
	case LDVSYNR:
	case LDHPDR:
	case LDVPDR:
	case LDHAJR:
		return true;
	default:
		return reg >= LDBnBBGCL(0) && reg <= LDBnBPPCR(3);
	}
}