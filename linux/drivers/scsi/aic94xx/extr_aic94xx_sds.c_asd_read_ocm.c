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
struct asd_ocm_dir {int dummy; } ;
struct asd_ha_struct {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int asd_get_bios_chim (struct asd_ha_struct*,struct asd_ocm_dir*) ; 
 scalar_t__ asd_hwi_check_ocm_access (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_printk (char*) ; 
 int asd_read_ocm_dir (struct asd_ha_struct*,struct asd_ocm_dir*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct asd_ocm_dir*) ; 
 struct asd_ocm_dir* kmalloc (int,int /*<<< orphan*/ ) ; 

int asd_read_ocm(struct asd_ha_struct *asd_ha)
{
	int err;
	struct asd_ocm_dir *dir;

	if (asd_hwi_check_ocm_access(asd_ha))
		return -1;

	dir = kmalloc(sizeof(*dir), GFP_KERNEL);
	if (!dir) {
		asd_printk("no memory for ocm dir\n");
		return -ENOMEM;
	}

	err = asd_read_ocm_dir(asd_ha, dir, 0);
	if (err)
		goto out;

	err = asd_get_bios_chim(asd_ha, dir);
out:
	kfree(dir);
	return err;
}