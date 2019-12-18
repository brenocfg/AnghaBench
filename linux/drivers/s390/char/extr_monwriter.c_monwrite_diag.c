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
struct monwrite_hdr {int /*<<< orphan*/  datalen; int /*<<< orphan*/  mod_level; int /*<<< orphan*/  release; int /*<<< orphan*/  version; int /*<<< orphan*/  record_num; int /*<<< orphan*/  applid; } ;
struct appldata_product_id {int /*<<< orphan*/  mod_lvl; int /*<<< orphan*/  release_nr; int /*<<< orphan*/  version_nr; int /*<<< orphan*/  record_nr; int /*<<< orphan*/  prod_fn; int /*<<< orphan*/  prod_nr; } ;
struct appldata_parameter_list {int /*<<< orphan*/  mod_lvl; int /*<<< orphan*/  release_nr; int /*<<< orphan*/  version_nr; int /*<<< orphan*/  record_nr; int /*<<< orphan*/  prod_fn; int /*<<< orphan*/  prod_nr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int appldata_asm (struct appldata_product_id*,struct appldata_product_id*,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct appldata_product_id*) ; 
 struct appldata_product_id* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int monwrite_diag(struct monwrite_hdr *myhdr, char *buffer, int fcn)
{
	struct appldata_parameter_list *parm_list;
	struct appldata_product_id *id;
	int rc;

	id = kmalloc(sizeof(*id), GFP_KERNEL);
	parm_list = kmalloc(sizeof(*parm_list), GFP_KERNEL);
	rc = -ENOMEM;
	if (!id || !parm_list)
		goto out;
	memcpy(id->prod_nr, "LNXAPPL", 7);
	id->prod_fn = myhdr->applid;
	id->record_nr = myhdr->record_num;
	id->version_nr = myhdr->version;
	id->release_nr = myhdr->release;
	id->mod_lvl = myhdr->mod_level;
	rc = appldata_asm(parm_list, id, fcn,
			  (void *) buffer, myhdr->datalen);
	if (rc <= 0)
		goto out;
	pr_err("Writing monitor data failed with rc=%i\n", rc);
	rc = (rc == 5) ? -EPERM : -EINVAL;
out:
	kfree(id);
	kfree(parm_list);
	return rc;
}