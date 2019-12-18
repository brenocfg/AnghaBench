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
typedef  int u32 ;
struct asus_wmi {int dummy; } ;

/* Variables and functions */
 int ASUS_WMI_DSTS_PRESENCE_BIT ; 
 int asus_wmi_get_devstate (struct asus_wmi*,int,int*) ; 

__attribute__((used)) static bool asus_wmi_dev_is_present(struct asus_wmi *asus, u32 dev_id)
{
	u32 retval;
	int status = asus_wmi_get_devstate(asus, dev_id, &retval);

	return status == 0 && (retval & ASUS_WMI_DSTS_PRESENCE_BIT);
}