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
typedef  int /*<<< orphan*/  u32 ;
struct xilly_endpoint {int idtlen; int dma_using_dac; int /*<<< orphan*/  dev; int /*<<< orphan*/  ep_wait; scalar_t__ registers; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  XILLY_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fpga_dma_control_reg ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xilly_quiesce(struct xilly_endpoint *endpoint)
{
	long t;

	endpoint->idtlen = -1;

	iowrite32((u32) (endpoint->dma_using_dac & 0x0001),
		  endpoint->registers + fpga_dma_control_reg);

	t = wait_event_interruptible_timeout(endpoint->ep_wait,
					     (endpoint->idtlen >= 0),
					     XILLY_TIMEOUT);
	if (t <= 0) {
		dev_err(endpoint->dev,
			"Failed to quiesce the device on exit.\n");
		return -ENODEV;
	}
	return 0;
}