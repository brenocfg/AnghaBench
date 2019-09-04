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
struct TYPE_4__ {TYPE_1__* mc_head; } ;
struct pvr2_v4l2_fh {unsigned int input_cnt; int* input_map; TYPE_2__ channel; } ;
struct pvr2_hdw {int dummy; } ;
struct pvr2_ctrl {int dummy; } ;
struct file {struct pvr2_v4l2_fh* private_data; } ;
struct TYPE_3__ {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_CID_INPUT ; 
 int pvr2_ctrl_get_value (struct pvr2_ctrl*,int*) ; 
 struct pvr2_ctrl* pvr2_hdw_get_ctrl_by_id (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvr2_g_input(struct file *file, void *priv, unsigned int *i)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	unsigned int idx;
	struct pvr2_ctrl *cptr;
	int val;
	int ret;

	cptr = pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_INPUT);
	val = 0;
	ret = pvr2_ctrl_get_value(cptr, &val);
	*i = 0;
	for (idx = 0; idx < fh->input_cnt; idx++) {
		if (fh->input_map[idx] == val) {
			*i = idx;
			break;
		}
	}
	return ret;
}