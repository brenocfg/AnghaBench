#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* mc_head; } ;
struct pvr2_v4l2_fh {TYPE_3__* pdi; TYPE_2__ channel; } ;
struct pvr2_hdw {int dummy; } ;
struct file {struct pvr2_v4l2_fh* private_data; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_6__ {int /*<<< orphan*/  stream; } ;
struct TYPE_4__ {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int EPERM ; 
 int pvr2_hdw_set_streaming (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvr2_streamoff(struct file *file, void *priv, enum v4l2_buf_type i)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;

	if (!fh->pdi->stream) {
		/* No stream defined for this node.  This means
		   that we're not currently allowed to stream from
		   this node. */
		return -EPERM;
	}
	return pvr2_hdw_set_streaming(hdw, 0);
}