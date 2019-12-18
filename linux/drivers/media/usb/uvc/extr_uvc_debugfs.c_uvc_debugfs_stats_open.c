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
struct uvc_streaming {int dummy; } ;
struct uvc_debugfs_buffer {int /*<<< orphan*/  data; int /*<<< orphan*/  count; } ;
struct inode {struct uvc_streaming* i_private; } ;
struct file {struct uvc_debugfs_buffer* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct uvc_debugfs_buffer* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_video_stats_dump (struct uvc_streaming*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int uvc_debugfs_stats_open(struct inode *inode, struct file *file)
{
	struct uvc_streaming *stream = inode->i_private;
	struct uvc_debugfs_buffer *buf;

	buf = kmalloc(sizeof(*buf), GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	buf->count = uvc_video_stats_dump(stream, buf->data, sizeof(buf->data));

	file->private_data = buf;
	return 0;
}