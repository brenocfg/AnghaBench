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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_thermal_rel_chrdev_count ; 
 scalar_t__ acpi_thermal_rel_chrdev_exclu ; 
 int /*<<< orphan*/  acpi_thermal_rel_chrdev_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_thermal_rel_release(struct inode *inode, struct file *file)
{
	spin_lock(&acpi_thermal_rel_chrdev_lock);
	acpi_thermal_rel_chrdev_count--;
	acpi_thermal_rel_chrdev_exclu = 0;
	spin_unlock(&acpi_thermal_rel_chrdev_lock);

	return 0;
}