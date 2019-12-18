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
struct v4l2_buffer {int /*<<< orphan*/  type; } ;
struct sh_veu_file {TYPE_1__* veu_dev; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  sh_veu_is_streamer (TYPE_1__*,struct sh_veu_file*,int /*<<< orphan*/ ) ; 
 int v4l2_m2m_querybuf (struct file*,int /*<<< orphan*/ ,struct v4l2_buffer*) ; 

__attribute__((used)) static int sh_veu_querybuf(struct file *file, void *priv,
			   struct v4l2_buffer *buf)
{
	struct sh_veu_file *veu_file = priv;

	if (!sh_veu_is_streamer(veu_file->veu_dev, veu_file, buf->type))
		return -EBUSY;

	return v4l2_m2m_querybuf(file, veu_file->veu_dev->m2m_ctx, buf);
}