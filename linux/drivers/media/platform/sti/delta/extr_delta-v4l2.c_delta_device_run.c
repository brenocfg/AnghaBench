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
struct delta_dev {int /*<<< orphan*/  work_queue; } ;
struct delta_ctx {int /*<<< orphan*/  run_work; struct delta_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void delta_device_run(void *priv)
{
	struct delta_ctx *ctx = priv;
	struct delta_dev *delta = ctx->dev;

	queue_work(delta->work_queue, &ctx->run_work);
}