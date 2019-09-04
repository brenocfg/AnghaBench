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
struct ipmi_user {int dummy; } ;

/* Variables and functions */
 scalar_t__ HP_BMC_PROD_ID ; 
 scalar_t__ HP_IANA_MFR_ID ; 
 int ipmi_version ; 
 scalar_t__ mfg_id ; 
 scalar_t__ prod_id ; 

__attribute__((used)) static int ipmi_hp_chassis_detect(struct ipmi_user *user)
{
	if (mfg_id == HP_IANA_MFR_ID
		&& prod_id == HP_BMC_PROD_ID
		&& ipmi_version == 1)
		return 1;
	return 0;
}