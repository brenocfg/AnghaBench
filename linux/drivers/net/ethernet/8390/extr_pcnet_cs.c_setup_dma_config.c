#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {struct net_device* priv; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int tx_start_page; int stop_page; int /*<<< orphan*/  block_output; int /*<<< orphan*/  block_input; int /*<<< orphan*/  get_8390_hdr; scalar_t__ rx_start_page; } ;

/* Variables and functions */
 scalar_t__ TX_PAGES ; 
 int /*<<< orphan*/  dma_block_input ; 
 int /*<<< orphan*/  dma_block_output ; 
 int /*<<< orphan*/  dma_get_8390_hdr ; 
 TYPE_1__ ei_status ; 

__attribute__((used)) static int setup_dma_config(struct pcmcia_device *link, int start_pg,
			    int stop_pg)
{
    struct net_device *dev = link->priv;

    ei_status.tx_start_page = start_pg;
    ei_status.rx_start_page = start_pg + TX_PAGES;
    ei_status.stop_page = stop_pg;

    /* set up block i/o functions */
    ei_status.get_8390_hdr = dma_get_8390_hdr;
    ei_status.block_input = dma_block_input;
    ei_status.block_output = dma_block_output;

    return 0;
}