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
struct idt_89hpesx_dev {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct idt_89hpesx_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  idt_free_pdev (struct idt_89hpesx_dev*) ; 
 int /*<<< orphan*/  idt_remove_dbgfs_files (struct idt_89hpesx_dev*) ; 
 int /*<<< orphan*/  idt_remove_sysfs_files (struct idt_89hpesx_dev*) ; 

__attribute__((used)) static int idt_remove(struct i2c_client *client)
{
	struct idt_89hpesx_dev *pdev = i2c_get_clientdata(client);

	/* Remove debugfs files first */
	idt_remove_dbgfs_files(pdev);

	/* Remove sysfs files */
	idt_remove_sysfs_files(pdev);

	/* Discard driver data structure */
	idt_free_pdev(pdev);

	return 0;
}