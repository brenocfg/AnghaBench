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
struct iscsi_boot_kset {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct iscsi_boot_kset* iscsi_boot_create_kset (char*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  kfree (char*) ; 

struct iscsi_boot_kset *iscsi_boot_create_host_kset(unsigned int hostno)
{
	struct iscsi_boot_kset *boot_kset;
	char *set_name;

	set_name = kasprintf(GFP_KERNEL, "iscsi_boot%u", hostno);
	if (!set_name)
		return NULL;

	boot_kset = iscsi_boot_create_kset(set_name);
	kfree(set_name);
	return boot_kset;
}