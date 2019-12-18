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
struct hva_dev {int /*<<< orphan*/  work_queue; } ;
struct hva_ctx {int /*<<< orphan*/  run_work; } ;

/* Variables and functions */
 struct hva_dev* ctx_to_hdev (struct hva_ctx*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hva_device_run(void *priv)
{
	struct hva_ctx *ctx = priv;
	struct hva_dev *hva = ctx_to_hdev(ctx);

	queue_work(hva->work_queue, &ctx->run_work);
}