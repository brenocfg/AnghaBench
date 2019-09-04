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
struct zpci_dev {int dummy; } ;
struct clp_fh_list_entry {int /*<<< orphan*/  config_state; int /*<<< orphan*/  fh; int /*<<< orphan*/  fid; int /*<<< orphan*/  vendor_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  clp_add_pci_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct zpci_dev* get_zdev_by_fid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __clp_add(struct clp_fh_list_entry *entry, void *data)
{
	struct zpci_dev *zdev;

	if (!entry->vendor_id)
		return;

	zdev = get_zdev_by_fid(entry->fid);
	if (!zdev)
		clp_add_pci_device(entry->fid, entry->fh, entry->config_state);
}