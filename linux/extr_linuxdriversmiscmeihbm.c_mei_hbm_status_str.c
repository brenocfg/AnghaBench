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
typedef  enum mei_hbm_status { ____Placeholder_mei_hbm_status } mei_hbm_status ;

/* Variables and functions */
#define  MEI_HBMS_ALREADY_EXISTS 135 
#define  MEI_HBMS_ALREADY_STARTED 134 
#define  MEI_HBMS_CLIENT_NOT_FOUND 133 
#define  MEI_HBMS_INVALID_PARAMETER 132 
#define  MEI_HBMS_NOT_ALLOWED 131 
#define  MEI_HBMS_NOT_STARTED 130 
#define  MEI_HBMS_REJECTED 129 
#define  MEI_HBMS_SUCCESS 128 

__attribute__((used)) static const char *mei_hbm_status_str(enum mei_hbm_status status)
{
#define MEI_HBM_STATUS(status) case MEI_HBMS_##status: return #status
	switch (status) {
	MEI_HBM_STATUS(SUCCESS);
	MEI_HBM_STATUS(CLIENT_NOT_FOUND);
	MEI_HBM_STATUS(ALREADY_EXISTS);
	MEI_HBM_STATUS(REJECTED);
	MEI_HBM_STATUS(INVALID_PARAMETER);
	MEI_HBM_STATUS(NOT_ALLOWED);
	MEI_HBM_STATUS(ALREADY_STARTED);
	MEI_HBM_STATUS(NOT_STARTED);
	default: return "unknown";
	}
#undef MEI_HBM_STATUS
}