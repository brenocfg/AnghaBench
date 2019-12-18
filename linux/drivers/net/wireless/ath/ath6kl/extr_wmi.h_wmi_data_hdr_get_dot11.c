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
struct wmi_data_hdr {int info; } ;

/* Variables and functions */
 int WMI_DATA_HDR_DATA_TYPE_802_11 ; 
 int WMI_DATA_HDR_DATA_TYPE_MASK ; 
 int WMI_DATA_HDR_DATA_TYPE_SHIFT ; 

__attribute__((used)) static inline u8 wmi_data_hdr_get_dot11(struct wmi_data_hdr *dhdr)
{
	u8 data_type;

	data_type = (dhdr->info >> WMI_DATA_HDR_DATA_TYPE_SHIFT) &
				   WMI_DATA_HDR_DATA_TYPE_MASK;
	return (data_type == WMI_DATA_HDR_DATA_TYPE_802_11);
}