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
 scalar_t__ IPMI_CPI1_MANUFACTURER_ID ; 
 scalar_t__ IPMI_CPI1_PRODUCT_ID ; 
 scalar_t__ mfg_id ; 
 scalar_t__ prod_id ; 

__attribute__((used)) static int ipmi_cpi1_detect(struct ipmi_user *user)
{
	return ((mfg_id == IPMI_CPI1_MANUFACTURER_ID)
		&& (prod_id == IPMI_CPI1_PRODUCT_ID));
}