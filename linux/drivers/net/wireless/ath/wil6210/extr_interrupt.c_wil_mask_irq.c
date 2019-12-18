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
struct wil6210_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wil6210_mask_irq_misc (struct wil6210_priv*,int) ; 
 int /*<<< orphan*/  wil6210_mask_irq_pseudo (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil6210_mask_irq_rx (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil6210_mask_irq_rx_edma (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil6210_mask_irq_tx (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil6210_mask_irq_tx_edma (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_dbg_irq (struct wil6210_priv*,char*) ; 

void wil_mask_irq(struct wil6210_priv *wil)
{
	wil_dbg_irq(wil, "mask_irq\n");

	wil6210_mask_irq_tx(wil);
	wil6210_mask_irq_tx_edma(wil);
	wil6210_mask_irq_rx(wil);
	wil6210_mask_irq_rx_edma(wil);
	wil6210_mask_irq_misc(wil, true);
	wil6210_mask_irq_pseudo(wil);
}