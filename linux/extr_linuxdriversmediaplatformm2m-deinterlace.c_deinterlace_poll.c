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
struct poll_table_struct {int dummy; } ;
struct file {struct deinterlace_ctx* private_data; } ;
struct deinterlace_ctx {TYPE_1__* dev; int /*<<< orphan*/  m2m_ctx; } ;
typedef  int /*<<< orphan*/  __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_poll (struct file*,int /*<<< orphan*/ ,struct poll_table_struct*) ; 

__attribute__((used)) static __poll_t deinterlace_poll(struct file *file,
				 struct poll_table_struct *wait)
{
	struct deinterlace_ctx *ctx = file->private_data;
	__poll_t ret;

	mutex_lock(&ctx->dev->dev_mutex);
	ret = v4l2_m2m_poll(file, ctx->m2m_ctx, wait);
	mutex_unlock(&ctx->dev->dev_mutex);

	return ret;
}