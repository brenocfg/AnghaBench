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
struct dma_device {int /*<<< orphan*/  channels; struct device* dev; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_config; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; int /*<<< orphan*/  device_prep_slave_sg; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  moxart_alloc_chan_resources ; 
 int /*<<< orphan*/  moxart_free_chan_resources ; 
 int /*<<< orphan*/  moxart_issue_pending ; 
 int /*<<< orphan*/  moxart_prep_slave_sg ; 
 int /*<<< orphan*/  moxart_slave_config ; 
 int /*<<< orphan*/  moxart_terminate_all ; 
 int /*<<< orphan*/  moxart_tx_status ; 

__attribute__((used)) static void moxart_dma_init(struct dma_device *dma, struct device *dev)
{
	dma->device_prep_slave_sg		= moxart_prep_slave_sg;
	dma->device_alloc_chan_resources	= moxart_alloc_chan_resources;
	dma->device_free_chan_resources		= moxart_free_chan_resources;
	dma->device_issue_pending		= moxart_issue_pending;
	dma->device_tx_status			= moxart_tx_status;
	dma->device_config			= moxart_slave_config;
	dma->device_terminate_all		= moxart_terminate_all;
	dma->dev				= dev;

	INIT_LIST_HEAD(&dma->channels);
}