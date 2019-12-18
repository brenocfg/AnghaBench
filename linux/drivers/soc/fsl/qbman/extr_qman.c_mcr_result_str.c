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
typedef  int u8 ;

/* Variables and functions */
#define  QM_MCR_RESULT_ERR_BADCOMMAND 134 
#define  QM_MCR_RESULT_ERR_FQID 133 
#define  QM_MCR_RESULT_ERR_FQSTATE 132 
#define  QM_MCR_RESULT_ERR_NOTEMPTY 131 
#define  QM_MCR_RESULT_NULL 130 
#define  QM_MCR_RESULT_OK 129 
#define  QM_MCR_RESULT_PENDING 128 

__attribute__((used)) static const char *mcr_result_str(u8 result)
{
	switch (result) {
	case QM_MCR_RESULT_NULL:
		return "QM_MCR_RESULT_NULL";
	case QM_MCR_RESULT_OK:
		return "QM_MCR_RESULT_OK";
	case QM_MCR_RESULT_ERR_FQID:
		return "QM_MCR_RESULT_ERR_FQID";
	case QM_MCR_RESULT_ERR_FQSTATE:
		return "QM_MCR_RESULT_ERR_FQSTATE";
	case QM_MCR_RESULT_ERR_NOTEMPTY:
		return "QM_MCR_RESULT_ERR_NOTEMPTY";
	case QM_MCR_RESULT_PENDING:
		return "QM_MCR_RESULT_PENDING";
	case QM_MCR_RESULT_ERR_BADCOMMAND:
		return "QM_MCR_RESULT_ERR_BADCOMMAND";
	}
	return "<unknown MCR result>";
}