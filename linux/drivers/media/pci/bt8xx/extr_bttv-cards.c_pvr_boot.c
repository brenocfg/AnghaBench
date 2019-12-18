#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr; TYPE_1__* pci; } ;
struct bttv {TYPE_2__ c; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int pvr_altera_load (struct bttv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pvr_boot(struct bttv *btv)
{
	const struct firmware *fw_entry;
	int rc;

	rc = request_firmware(&fw_entry, "hcwamc.rbf", &btv->c.pci->dev);
	if (rc != 0) {
		pr_warn("%d: no altera firmware [via hotplug]\n", btv->c.nr);
		return rc;
	}
	rc = pvr_altera_load(btv, fw_entry->data, fw_entry->size);
	pr_info("%d: altera firmware upload %s\n",
		btv->c.nr, (rc < 0) ? "failed" : "ok");
	release_firmware(fw_entry);
	return rc;
}