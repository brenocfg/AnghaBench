#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_querymenu {scalar_t__* name; int /*<<< orphan*/  index; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__* mc_head; } ;
struct pvr2_v4l2_fh {TYPE_2__ channel; } ;
struct pvr2_hdw {int dummy; } ;
struct file {struct pvr2_v4l2_fh* private_data; } ;
struct TYPE_3__ {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int pvr2_ctrl_get_valname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,unsigned int*) ; 
 int /*<<< orphan*/  pvr2_hdw_get_ctrl_v4l (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvr2_querymenu(struct file *file, void *priv, struct v4l2_querymenu *vm)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	unsigned int cnt = 0;
	int ret;

	ret = pvr2_ctrl_get_valname(pvr2_hdw_get_ctrl_v4l(hdw, vm->id),
			vm->index,
			vm->name, sizeof(vm->name) - 1,
			&cnt);
	vm->name[cnt] = 0;
	return ret;
}