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
struct hsu_dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hsu_dma_chan_start (struct hsu_dma_chan*) ; 

__attribute__((used)) static void hsu_dma_start_channel(struct hsu_dma_chan *hsuc)
{
	hsu_dma_chan_start(hsuc);
}