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
struct TYPE_2__ {int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; int /*<<< orphan*/  id_table; int /*<<< orphan*/  name; } ;
struct saa7146_extension {TYPE_1__ driver; int /*<<< orphan*/  name; int /*<<< orphan*/  pci_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_EE (char*,struct saa7146_extension*) ; 
 int pci_register_driver (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_init_one ; 
 int /*<<< orphan*/  saa7146_remove_one ; 

int saa7146_register_extension(struct saa7146_extension* ext)
{
	DEB_EE("ext:%p\n", ext);

	ext->driver.name = ext->name;
	ext->driver.id_table = ext->pci_tbl;
	ext->driver.probe = saa7146_init_one;
	ext->driver.remove = saa7146_remove_one;

	pr_info("register extension '%s'\n", ext->name);
	return pci_register_driver(&ext->driver);
}