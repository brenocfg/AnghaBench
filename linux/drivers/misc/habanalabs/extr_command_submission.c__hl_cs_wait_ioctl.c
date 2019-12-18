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
typedef  unsigned long u64 ;
struct hl_device {int dummy; } ;
struct hl_ctx {int dummy; } ;
struct dma_fence {long error; } ;

/* Variables and functions */
 long EIO ; 
 long ETIMEDOUT ; 
 scalar_t__ IS_ERR (struct dma_fence*) ; 
 unsigned long MAX_SCHEDULE_TIMEOUT ; 
 long PTR_ERR (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 long dma_fence_wait_timeout (struct dma_fence*,int,unsigned long) ; 
 int /*<<< orphan*/  hl_ctx_get (struct hl_device*,struct hl_ctx*) ; 
 struct dma_fence* hl_ctx_get_fence (struct hl_ctx*,unsigned long) ; 
 int /*<<< orphan*/  hl_ctx_put (struct hl_ctx*) ; 
 unsigned long usecs_to_jiffies (unsigned long) ; 

__attribute__((used)) static long _hl_cs_wait_ioctl(struct hl_device *hdev,
		struct hl_ctx *ctx, u64 timeout_us, u64 seq)
{
	struct dma_fence *fence;
	unsigned long timeout;
	long rc;

	if (timeout_us == MAX_SCHEDULE_TIMEOUT)
		timeout = timeout_us;
	else
		timeout = usecs_to_jiffies(timeout_us);

	hl_ctx_get(hdev, ctx);

	fence = hl_ctx_get_fence(ctx, seq);
	if (IS_ERR(fence)) {
		rc = PTR_ERR(fence);
	} else if (fence) {
		rc = dma_fence_wait_timeout(fence, true, timeout);
		if (fence->error == -ETIMEDOUT)
			rc = -ETIMEDOUT;
		else if (fence->error == -EIO)
			rc = -EIO;
		dma_fence_put(fence);
	} else
		rc = 1;

	hl_ctx_put(ctx);

	return rc;
}