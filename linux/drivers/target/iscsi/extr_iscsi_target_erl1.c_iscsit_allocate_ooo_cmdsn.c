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
struct iscsi_ooo_cmdsn {int /*<<< orphan*/  ooo_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct iscsi_ooo_cmdsn* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_ooo_cache ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static struct iscsi_ooo_cmdsn *iscsit_allocate_ooo_cmdsn(void)
{
	struct iscsi_ooo_cmdsn *ooo_cmdsn = NULL;

	ooo_cmdsn = kmem_cache_zalloc(lio_ooo_cache, GFP_ATOMIC);
	if (!ooo_cmdsn) {
		pr_err("Unable to allocate memory for"
			" struct iscsi_ooo_cmdsn.\n");
		return NULL;
	}
	INIT_LIST_HEAD(&ooo_cmdsn->ooo_list);

	return ooo_cmdsn;
}