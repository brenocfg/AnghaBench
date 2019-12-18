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
typedef  int /*<<< orphan*/  u32 ;
struct asus_wmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DSTS_STATUS_BIT ; 
 int asus_wmi_get_devstate_bits (struct asus_wmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asus_wmi_get_devstate_simple(struct asus_wmi *asus, u32 dev_id)
{
	return asus_wmi_get_devstate_bits(asus, dev_id,
					  ASUS_WMI_DSTS_STATUS_BIT);
}