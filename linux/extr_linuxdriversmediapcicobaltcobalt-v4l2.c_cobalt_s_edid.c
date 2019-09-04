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
typedef  int u32 ;
struct v4l2_edid {int pad; } ;
struct file {int dummy; } ;
struct cobalt_stream {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  set_edid ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct v4l2_edid*) ; 
 struct cobalt_stream* video_drvdata (struct file*) ; 

__attribute__((used)) static int cobalt_s_edid(struct file *file, void *fh, struct v4l2_edid *edid)
{
	struct cobalt_stream *s = video_drvdata(file);
	u32 pad = edid->pad;
	int ret;

	if (edid->pad >= 2)
		return -EINVAL;
	edid->pad = 0;
	ret = v4l2_subdev_call(s->sd, pad, set_edid, edid);
	edid->pad = pad;
	return ret;
}