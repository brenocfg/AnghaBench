#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  debugfs_entry; } ;
struct hva_dev {TYPE_1__ dbg; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVA_NAME ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device ; 
 int /*<<< orphan*/  encoders ; 
 int /*<<< orphan*/  hva_dbg_create_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hva_debugfs_remove (struct hva_dev*) ; 
 int /*<<< orphan*/  last ; 
 int /*<<< orphan*/  regs ; 

void hva_debugfs_create(struct hva_dev *hva)
{
	hva->dbg.debugfs_entry = debugfs_create_dir(HVA_NAME, NULL);
	if (!hva->dbg.debugfs_entry)
		goto err;

	if (!hva_dbg_create_entry(device))
		goto err;

	if (!hva_dbg_create_entry(encoders))
		goto err;

	if (!hva_dbg_create_entry(last))
		goto err;

	if (!hva_dbg_create_entry(regs))
		goto err;

	return;

err:
	hva_debugfs_remove(hva);
}