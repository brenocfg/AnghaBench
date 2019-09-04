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
struct poll_table_struct {int dummy; } ;
struct file {struct emmaprp_ctx* private_data; } ;
struct emmaprp_dev {int /*<<< orphan*/  dev_mutex; } ;
struct emmaprp_ctx {int /*<<< orphan*/  m2m_ctx; } ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_poll (struct file*,int /*<<< orphan*/ ,struct poll_table_struct*) ; 
 struct emmaprp_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static __poll_t emmaprp_poll(struct file *file,
				 struct poll_table_struct *wait)
{
	struct emmaprp_dev *pcdev = video_drvdata(file);
	struct emmaprp_ctx *ctx = file->private_data;
	__poll_t res;

	mutex_lock(&pcdev->dev_mutex);
	res = v4l2_m2m_poll(file, ctx->m2m_ctx, wait);
	mutex_unlock(&pcdev->dev_mutex);
	return res;
}