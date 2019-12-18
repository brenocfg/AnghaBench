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
struct uld_ctx {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  c4iw_dealloc (struct uld_ctx*) ; 
 int /*<<< orphan*/  c4iw_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void c4iw_remove(struct uld_ctx *ctx)
{
	pr_debug("c4iw_dev %p\n", ctx->dev);
	c4iw_unregister_device(ctx->dev);
	c4iw_dealloc(ctx);
}