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
struct picolcd_data {int /*<<< orphan*/  mutex_flash; struct dentry* debug_flash; struct dentry* debug_eeprom; struct dentry* debug_reset; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (struct dentry*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void picolcd_exit_devfs(struct picolcd_data *data)
{
	struct dentry *dent;

	dent = data->debug_reset;
	data->debug_reset = NULL;
	debugfs_remove(dent);
	dent = data->debug_eeprom;
	data->debug_eeprom = NULL;
	debugfs_remove(dent);
	dent = data->debug_flash;
	data->debug_flash = NULL;
	debugfs_remove(dent);
	mutex_destroy(&data->mutex_flash);
}