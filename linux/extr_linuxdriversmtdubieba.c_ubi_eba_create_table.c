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
struct ubi_volume {int dummy; } ;
struct ubi_eba_table {struct ubi_eba_table* entries; int /*<<< orphan*/  pnum; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ubi_eba_table* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UBI_LEB_UNMAPPED ; 
 int /*<<< orphan*/  kfree (struct ubi_eba_table*) ; 
 struct ubi_eba_table* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 struct ubi_eba_table* kzalloc (int,int /*<<< orphan*/ ) ; 

struct ubi_eba_table *ubi_eba_create_table(struct ubi_volume *vol,
					   int nentries)
{
	struct ubi_eba_table *tbl;
	int err = -ENOMEM;
	int i;

	tbl = kzalloc(sizeof(*tbl), GFP_KERNEL);
	if (!tbl)
		return ERR_PTR(-ENOMEM);

	tbl->entries = kmalloc_array(nentries, sizeof(*tbl->entries),
				     GFP_KERNEL);
	if (!tbl->entries)
		goto err;

	for (i = 0; i < nentries; i++)
		tbl->entries[i].pnum = UBI_LEB_UNMAPPED;

	return tbl;

err:
	kfree(tbl->entries);
	kfree(tbl);

	return ERR_PTR(err);
}