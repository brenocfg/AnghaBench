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
struct kobject {int dummy; } ;
struct efivar_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct efivar_entry*) ; 
 struct efivar_entry* to_efivar_entry (struct kobject*) ; 

__attribute__((used)) static void efivar_release(struct kobject *kobj)
{
	struct efivar_entry *var = to_efivar_entry(kobj);
	kfree(var);
}