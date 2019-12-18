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
struct hl_device {int /*<<< orphan*/  dev; } ;
struct hl_ctx {int /*<<< orphan*/  asid; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hl_ctx_do_release ; 
 int kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void hl_ctx_free(struct hl_device *hdev, struct hl_ctx *ctx)
{
	if (kref_put(&ctx->refcount, hl_ctx_do_release) == 1)
		return;

	dev_warn(hdev->dev,
		"Context %d closed or terminated but its CS are executing\n",
		ctx->asid);
}