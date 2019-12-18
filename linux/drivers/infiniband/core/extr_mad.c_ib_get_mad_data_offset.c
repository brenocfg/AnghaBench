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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ IB_MGMT_CLASS_BIS ; 
 scalar_t__ IB_MGMT_CLASS_DEVICE_ADM ; 
 scalar_t__ IB_MGMT_CLASS_DEVICE_MGMT ; 
 scalar_t__ IB_MGMT_CLASS_SUBN_ADM ; 
 scalar_t__ IB_MGMT_CLASS_VENDOR_RANGE2_END ; 
 scalar_t__ IB_MGMT_CLASS_VENDOR_RANGE2_START ; 
 int IB_MGMT_DEVICE_HDR ; 
 int IB_MGMT_MAD_HDR ; 
 int IB_MGMT_SA_HDR ; 
 int IB_MGMT_VENDOR_HDR ; 

int ib_get_mad_data_offset(u8 mgmt_class)
{
	if (mgmt_class == IB_MGMT_CLASS_SUBN_ADM)
		return IB_MGMT_SA_HDR;
	else if ((mgmt_class == IB_MGMT_CLASS_DEVICE_MGMT) ||
		 (mgmt_class == IB_MGMT_CLASS_DEVICE_ADM) ||
		 (mgmt_class == IB_MGMT_CLASS_BIS))
		return IB_MGMT_DEVICE_HDR;
	else if ((mgmt_class >= IB_MGMT_CLASS_VENDOR_RANGE2_START) &&
		 (mgmt_class <= IB_MGMT_CLASS_VENDOR_RANGE2_END))
		return IB_MGMT_VENDOR_HDR;
	else
		return IB_MGMT_MAD_HDR;
}