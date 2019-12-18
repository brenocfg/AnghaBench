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
struct xgbe_desc_if {int /*<<< orphan*/  (* free_ring_resources ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {struct xgbe_desc_if desc_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_free_channels (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_free_memory(struct xgbe_prv_data *pdata)
{
	struct xgbe_desc_if *desc_if = &pdata->desc_if;

	/* Free the ring descriptors and buffers */
	desc_if->free_ring_resources(pdata);

	/* Free the channel and ring structures */
	xgbe_free_channels(pdata);
}