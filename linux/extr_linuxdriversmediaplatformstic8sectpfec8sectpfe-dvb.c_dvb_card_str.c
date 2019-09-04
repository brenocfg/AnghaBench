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
#define  STV0367_TDA18212_NIMA_1 133 
#define  STV0367_TDA18212_NIMA_2 132 
#define  STV0367_TDA18212_NIMB_1 131 
#define  STV0367_TDA18212_NIMB_2 130 
#define  STV0903_6110_LNB24_NIMA 129 
#define  STV0903_6110_LNB24_NIMB 128 

__attribute__((used)) static inline const char *dvb_card_str(unsigned int c)
{
	switch (c) {
	case STV0367_TDA18212_NIMA_1:	return "STV0367_TDA18212_NIMA_1";
	case STV0367_TDA18212_NIMA_2:	return "STV0367_TDA18212_NIMA_2";
	case STV0367_TDA18212_NIMB_1:	return "STV0367_TDA18212_NIMB_1";
	case STV0367_TDA18212_NIMB_2:	return "STV0367_TDA18212_NIMB_2";
	case STV0903_6110_LNB24_NIMA:	return "STV0903_6110_LNB24_NIMA";
	case STV0903_6110_LNB24_NIMB:	return "STV0903_6110_LNB24_NIMB";
	default:			return "unknown dvb frontend card";
	}
}