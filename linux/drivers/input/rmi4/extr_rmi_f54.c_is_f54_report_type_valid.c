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
struct f54_data {int capabilities; } ;
typedef  enum rmi_f54_report_type { ____Placeholder_rmi_f54_report_type } rmi_f54_report_type ;

/* Variables and functions */
#define  F54_16BIT_IMAGE 133 
#define  F54_8BIT_IMAGE 132 
 int F54_CAP_IMAGE16 ; 
 int F54_CAP_IMAGE8 ; 
#define  F54_FULL_RAW_CAP 131 
#define  F54_FULL_RAW_CAP_RX_OFFSET_REMOVED 130 
#define  F54_RAW_16BIT_IMAGE 129 
#define  F54_TRUE_BASELINE 128 

__attribute__((used)) static bool is_f54_report_type_valid(struct f54_data *f54,
				     enum rmi_f54_report_type reptype)
{
	switch (reptype) {
	case F54_8BIT_IMAGE:
		return f54->capabilities & F54_CAP_IMAGE8;
	case F54_16BIT_IMAGE:
	case F54_RAW_16BIT_IMAGE:
		return f54->capabilities & F54_CAP_IMAGE16;
	case F54_TRUE_BASELINE:
		return f54->capabilities & F54_CAP_IMAGE16;
	case F54_FULL_RAW_CAP:
	case F54_FULL_RAW_CAP_RX_OFFSET_REMOVED:
		return true;
	default:
		return false;
	}
}