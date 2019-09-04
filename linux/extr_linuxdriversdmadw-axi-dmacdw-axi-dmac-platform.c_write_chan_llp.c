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
struct axi_dma_chan {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CH_LLP ; 
 int /*<<< orphan*/  axi_chan_iowrite64 (struct axi_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_chan_llp(struct axi_dma_chan *chan, dma_addr_t adr)
{
	axi_chan_iowrite64(chan, CH_LLP, adr);
}