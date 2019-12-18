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
struct csio_lnode {TYPE_1__* fcfinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  csio_cleanup_rns (struct csio_lnode*) ; 
 scalar_t__ csio_fdmi_enable ; 
 int /*<<< orphan*/  csio_free_fcfinfo ; 
 scalar_t__ csio_is_npiv_ln (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_ln_fdmi_exit (struct csio_lnode*) ; 
 struct csio_lnode* csio_parent_lnode (struct csio_lnode*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
csio_ln_exit(struct csio_lnode *ln)
{
	struct csio_lnode *pln;

	csio_cleanup_rns(ln);
	if (csio_is_npiv_ln(ln)) {
		pln = csio_parent_lnode(ln);
		kref_put(&pln->fcfinfo->kref, csio_free_fcfinfo);
	} else {
		kref_put(&ln->fcfinfo->kref, csio_free_fcfinfo);
		if (csio_fdmi_enable)
			csio_ln_fdmi_exit(ln);
	}
	ln->fcfinfo = NULL;
}