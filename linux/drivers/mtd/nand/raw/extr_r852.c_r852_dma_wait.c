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
struct r852_device {int /*<<< orphan*/  dma_done; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r852_dma_wait(struct r852_device *dev)
{
	long timeout = wait_for_completion_timeout(&dev->dma_done,
				msecs_to_jiffies(1000));
	if (!timeout) {
		dbg("timeout waiting for DMA interrupt");
		return -ETIMEDOUT;
	}

	return 0;
}