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
struct tee_context {int /*<<< orphan*/  teedev; } ;

/* Variables and functions */
 int /*<<< orphan*/  tee_device_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teedev_ctx_put (struct tee_context*) ; 

__attribute__((used)) static void teedev_close_context(struct tee_context *ctx)
{
	tee_device_put(ctx->teedev);
	teedev_ctx_put(ctx);
}