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
struct pvr2_v4l2_fh {struct pvr2_v4l2_dev* pdi; TYPE_2__ channel; } ;
struct pvr2_v4l2_dev {int /*<<< orphan*/  config; int /*<<< orphan*/  stream; } ;
struct pvr2_hdw {int dummy; } ;
struct file {struct pvr2_v4l2_fh* private_data; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_3__ {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int EPERM ; 
 int pvr2_hdw_set_stream_type (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 
 int pvr2_hdw_set_streaming (struct pvr2_hdw*,int) ; 

__attribute__((used)) static int pvr2_streamon(struct file *file, void *priv, enum v4l2_buf_type i)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	struct pvr2_v4l2_dev *pdi = fh->pdi;
	int ret;

	if (!fh->pdi->stream) {
		/* No stream defined for this node.  This means
		   that we're not currently allowed to stream from
		   this node. */
		return -EPERM;
	}
	ret = pvr2_hdw_set_stream_type(hdw, pdi->config);
	if (ret < 0)
		return ret;
	return pvr2_hdw_set_streaming(hdw, !0);
}