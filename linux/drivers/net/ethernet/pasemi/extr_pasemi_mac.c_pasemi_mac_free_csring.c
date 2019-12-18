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
struct pasemi_mac_csring {int /*<<< orphan*/  fun; int /*<<< orphan*/  chan; int /*<<< orphan*/ * events; } ;

/* Variables and functions */
 int /*<<< orphan*/  pasemi_dma_free_chan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pasemi_dma_free_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pasemi_dma_free_fun (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pasemi_dma_free_ring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pasemi_dma_stop_chan (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pasemi_mac_free_csring(struct pasemi_mac_csring *csring)
{
	pasemi_dma_stop_chan(&csring->chan);
	pasemi_dma_free_flag(csring->events[0]);
	pasemi_dma_free_flag(csring->events[1]);
	pasemi_dma_free_ring(&csring->chan);
	pasemi_dma_free_chan(&csring->chan);
	pasemi_dma_free_fun(csring->fun);
}