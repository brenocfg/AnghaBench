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
struct vb2_queue {int dummy; } ;
struct s5p_jpeg_ctx {TYPE_1__* jpeg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 struct s5p_jpeg_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int s5p_jpeg_start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct s5p_jpeg_ctx *ctx = vb2_get_drv_priv(q);
	int ret;

	ret = pm_runtime_get_sync(ctx->jpeg->dev);

	return ret > 0 ? 0 : ret;
}