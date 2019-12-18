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
struct comedi_isadma_desc {int /*<<< orphan*/  chan; int /*<<< orphan*/  size; int /*<<< orphan*/  hw_addr; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  set_dma_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void comedi_isadma_program(struct comedi_isadma_desc *desc)
{
	unsigned long flags;

	flags = claim_dma_lock();
	clear_dma_ff(desc->chan);
	set_dma_mode(desc->chan, desc->mode);
	set_dma_addr(desc->chan, desc->hw_addr);
	set_dma_count(desc->chan, desc->size);
	enable_dma(desc->chan);
	release_dma_lock(flags);
}