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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 scalar_t__ H_AUTHORITY ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 

__attribute__((used)) static void ehea_promiscuous_error(u64 hret, int enable)
{
	if (hret == H_AUTHORITY)
		pr_info("Hypervisor denied %sabling promiscuous mode\n",
			enable == 1 ? "en" : "dis");
	else
		pr_err("failed %sabling promiscuous mode\n",
		       enable == 1 ? "en" : "dis");
}