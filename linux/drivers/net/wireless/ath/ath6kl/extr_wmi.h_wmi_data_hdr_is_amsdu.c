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
struct wmi_data_hdr {int /*<<< orphan*/  info2; } ;

/* Variables and functions */
 int WMI_DATA_HDR_AMSDU_MASK ; 
 int WMI_DATA_HDR_AMSDU_SHIFT ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 wmi_data_hdr_is_amsdu(struct wmi_data_hdr *dhdr)
{
	return (le16_to_cpu(dhdr->info2) >> WMI_DATA_HDR_AMSDU_SHIFT) &
			       WMI_DATA_HDR_AMSDU_MASK;
}