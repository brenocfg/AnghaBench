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
struct hsu_dma_chan {int /*<<< orphan*/  vchan; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct hsu_dma_chan* to_hsu_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_synchronize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hsu_dma_synchronize(struct dma_chan *chan)
{
	struct hsu_dma_chan *hsuc = to_hsu_dma_chan(chan);

	vchan_synchronize(&hsuc->vchan);
}