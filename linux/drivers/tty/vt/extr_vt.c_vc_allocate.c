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
struct vt_notifier_param {struct vc_data* vc; } ;
struct vc_data {int vc_screenbuf_size; int /*<<< orphan*/  vc_cols; int /*<<< orphan*/  vc_rows; void* vc_screenbuf; int /*<<< orphan*/ * vc_uni_pagedir_loc; int /*<<< orphan*/  port; } ;
struct TYPE_2__ {struct vc_data* d; int /*<<< orphan*/  SAK_work; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int MAX_NR_CONSOLES ; 
 int /*<<< orphan*/  VT_ALLOCATE ; 
 int /*<<< orphan*/  WARN_CONSOLE_UNLOCKED () ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vt_notifier_param*) ; 
 int /*<<< orphan*/  con_set_default_unimap (struct vc_data*) ; 
 int global_cursor_default ; 
 int /*<<< orphan*/  kfree (struct vc_data*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_port_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_SAK ; 
 TYPE_1__* vc_cons ; 
 int /*<<< orphan*/  vc_init (struct vc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vcs_make_sysfs (unsigned int) ; 
 int /*<<< orphan*/  visual_deinit (struct vc_data*) ; 
 int /*<<< orphan*/  visual_init (struct vc_data*,unsigned int,int) ; 
 int /*<<< orphan*/  vt_notifier_list ; 

int vc_allocate(unsigned int currcons)	/* return 0 on success */
{
	struct vt_notifier_param param;
	struct vc_data *vc;

	WARN_CONSOLE_UNLOCKED();

	if (currcons >= MAX_NR_CONSOLES)
		return -ENXIO;

	if (vc_cons[currcons].d)
		return 0;

	/* due to the granularity of kmalloc, we waste some memory here */
	/* the alloc is done in two steps, to optimize the common situation
	   of a 25x80 console (structsize=216, screenbuf_size=4000) */
	/* although the numbers above are not valid since long ago, the
	   point is still up-to-date and the comment still has its value
	   even if only as a historical artifact.  --mj, July 1998 */
	param.vc = vc = kzalloc(sizeof(struct vc_data), GFP_KERNEL);
	if (!vc)
		return -ENOMEM;

	vc_cons[currcons].d = vc;
	tty_port_init(&vc->port);
	INIT_WORK(&vc_cons[currcons].SAK_work, vc_SAK);

	visual_init(vc, currcons, 1);

	if (!*vc->vc_uni_pagedir_loc)
		con_set_default_unimap(vc);

	vc->vc_screenbuf = kzalloc(vc->vc_screenbuf_size, GFP_KERNEL);
	if (!vc->vc_screenbuf)
		goto err_free;

	/* If no drivers have overridden us and the user didn't pass a
	   boot option, default to displaying the cursor */
	if (global_cursor_default == -1)
		global_cursor_default = 1;

	vc_init(vc, vc->vc_rows, vc->vc_cols, 1);
	vcs_make_sysfs(currcons);
	atomic_notifier_call_chain(&vt_notifier_list, VT_ALLOCATE, &param);

	return 0;
err_free:
	visual_deinit(vc);
	kfree(vc);
	vc_cons[currcons].d = NULL;
	return -ENOMEM;
}