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
struct msgdma_device {int /*<<< orphan*/  slave_cfg; } ;
struct dma_slave_config {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dma_slave_config*,int) ; 
 struct msgdma_device* to_mdev (struct dma_chan*) ; 

__attribute__((used)) static int msgdma_dma_config(struct dma_chan *dchan,
			     struct dma_slave_config *config)
{
	struct msgdma_device *mdev = to_mdev(dchan);

	memcpy(&mdev->slave_cfg, config, sizeof(*config));

	return 0;
}