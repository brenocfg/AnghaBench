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
struct saa7146_extension {int /*<<< orphan*/  driver; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_EE (char*,struct saa7146_extension*) ; 
 int /*<<< orphan*/  pci_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

int saa7146_unregister_extension(struct saa7146_extension* ext)
{
	DEB_EE("ext:%p\n", ext);
	pr_info("unregister extension '%s'\n", ext->name);
	pci_unregister_driver(&ext->driver);
	return 0;
}