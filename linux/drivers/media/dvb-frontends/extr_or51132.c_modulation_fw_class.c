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
typedef  enum fe_modulation { ____Placeholder_fe_modulation } fe_modulation ;

/* Variables and functions */
 int MOD_FWCLASS_QAM ; 
 int MOD_FWCLASS_UNKNOWN ; 
 int MOD_FWCLASS_VSB ; 
#define  QAM_256 131 
#define  QAM_64 130 
#define  QAM_AUTO 129 
#define  VSB_8 128 

__attribute__((used)) static int modulation_fw_class(enum fe_modulation modulation)
{
	switch(modulation) {
	case VSB_8:
		return MOD_FWCLASS_VSB;
	case QAM_AUTO:
	case QAM_64:
	case QAM_256:
		return MOD_FWCLASS_QAM;
	default:
		return MOD_FWCLASS_UNKNOWN;
	}
}