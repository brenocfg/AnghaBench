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
struct vsp1_dl_manager {int /*<<< orphan*/  cmdpool; } ;
struct vsp1_dl_list {struct vsp1_dl_ext_cmd* pre_cmd; struct vsp1_dl_manager* dlm; } ;
struct vsp1_dl_ext_cmd {int dummy; } ;

/* Variables and functions */
 struct vsp1_dl_ext_cmd* vsp1_dl_ext_cmd_get (int /*<<< orphan*/ ) ; 

struct vsp1_dl_ext_cmd *vsp1_dl_get_pre_cmd(struct vsp1_dl_list *dl)
{
	struct vsp1_dl_manager *dlm = dl->dlm;

	if (dl->pre_cmd)
		return dl->pre_cmd;

	dl->pre_cmd = vsp1_dl_ext_cmd_get(dlm->cmdpool);

	return dl->pre_cmd;
}