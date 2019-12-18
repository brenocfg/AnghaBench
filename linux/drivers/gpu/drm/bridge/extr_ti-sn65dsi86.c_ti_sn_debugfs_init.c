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
struct ti_sn_bridge {int /*<<< orphan*/  debugfs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct ti_sn_bridge*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status_fops ; 

__attribute__((used)) static void ti_sn_debugfs_init(struct ti_sn_bridge *pdata)
{
	pdata->debugfs = debugfs_create_dir(dev_name(pdata->dev), NULL);

	debugfs_create_file("status", 0600, pdata->debugfs, pdata,
			&status_fops);
}