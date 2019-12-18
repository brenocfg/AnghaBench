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
 int __coda_start_decoding (struct coda_ctx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int coda_start_decoding(struct coda_ctx *ctx)
{
	struct coda_dev *dev = ctx->dev;
	int ret;

	mutex_lock(&dev->coda_mutex);
	ret = __coda_start_decoding(ctx);
	mutex_unlock(&dev->coda_mutex);

	return ret;
}