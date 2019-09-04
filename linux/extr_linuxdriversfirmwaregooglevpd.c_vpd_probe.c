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
struct TYPE_2__ {int /*<<< orphan*/  cbmem_addr; } ;
struct coreboot_device {TYPE_1__ cbmem_ref; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  firmware_kobj ; 
 int /*<<< orphan*/  kobject_create_and_add (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpd_kobj ; 
 int vpd_sections_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpd_probe(struct coreboot_device *dev)
{
	int ret;

	vpd_kobj = kobject_create_and_add("vpd", firmware_kobj);
	if (!vpd_kobj)
		return -ENOMEM;

	ret = vpd_sections_init(dev->cbmem_ref.cbmem_addr);
	if (ret) {
		kobject_put(vpd_kobj);
		return ret;
	}

	return 0;
}