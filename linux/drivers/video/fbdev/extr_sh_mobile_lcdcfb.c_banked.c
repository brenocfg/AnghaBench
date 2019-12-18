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

/* Variables and functions */
#define  LDDFR 139 
#define  LDHCNR 138 
#define  LDHSYNR 137 
#define  LDMLSR 136 
#define  LDMT1R 135 
#define  LDMT2R 134 
#define  LDMT3R 133 
#define  LDSA1R 132 
#define  LDSA2R 131 
#define  LDSM1R 130 
#define  LDVLNR 129 
#define  LDVSYNR 128 

__attribute__((used)) static bool banked(int reg_nr)
{
	switch (reg_nr) {
	case LDMT1R:
	case LDMT2R:
	case LDMT3R:
	case LDDFR:
	case LDSM1R:
	case LDSA1R:
	case LDSA2R:
	case LDMLSR:
	case LDHCNR:
	case LDHSYNR:
	case LDVLNR:
	case LDVSYNR:
		return true;
	}
	return false;
}