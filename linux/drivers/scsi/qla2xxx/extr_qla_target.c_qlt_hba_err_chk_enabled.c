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
struct se_cmd {int prot_op; } ;

/* Variables and functions */
#define  TARGET_PROT_DIN_INSERT 133 
#define  TARGET_PROT_DIN_PASS 132 
#define  TARGET_PROT_DIN_STRIP 131 
#define  TARGET_PROT_DOUT_INSERT 130 
#define  TARGET_PROT_DOUT_PASS 129 
#define  TARGET_PROT_DOUT_STRIP 128 
 int ql2xenablehba_err_chk ; 

__attribute__((used)) static inline int
qlt_hba_err_chk_enabled(struct se_cmd *se_cmd)
{
	switch (se_cmd->prot_op) {
	case TARGET_PROT_DOUT_INSERT:
	case TARGET_PROT_DIN_STRIP:
		if (ql2xenablehba_err_chk >= 1)
			return 1;
		break;
	case TARGET_PROT_DOUT_PASS:
	case TARGET_PROT_DIN_PASS:
		if (ql2xenablehba_err_chk >= 2)
			return 1;
		break;
	case TARGET_PROT_DIN_INSERT:
	case TARGET_PROT_DOUT_STRIP:
		return 1;
	default:
		break;
	}
	return 0;
}