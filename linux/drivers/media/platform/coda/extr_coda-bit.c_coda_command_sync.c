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
struct coda_dev {int /*<<< orphan*/  coda_mutex; } ;
struct coda_ctx {struct coda_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  coda_command_async (struct coda_ctx*,int) ; 
 int coda_wait_timeout (struct coda_dev*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_coda_bit_done (struct coda_ctx*) ; 

__attribute__((used)) static int coda_command_sync(struct coda_ctx *ctx, int cmd)
{
	struct coda_dev *dev = ctx->dev;
	int ret;

	lockdep_assert_held(&dev->coda_mutex);

	coda_command_async(ctx, cmd);
	ret = coda_wait_timeout(dev);
	trace_coda_bit_done(ctx);

	return ret;
}