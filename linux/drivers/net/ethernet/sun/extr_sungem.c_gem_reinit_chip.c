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
struct gem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gem_disable_ints (struct gem*) ; 
 int /*<<< orphan*/  gem_init_dma (struct gem*) ; 
 int /*<<< orphan*/  gem_init_mac (struct gem*) ; 
 int /*<<< orphan*/  gem_init_pause_thresholds (struct gem*) ; 
 int /*<<< orphan*/  gem_init_rings (struct gem*) ; 
 int /*<<< orphan*/  gem_reset (struct gem*) ; 

__attribute__((used)) static void gem_reinit_chip(struct gem *gp)
{
	/* Reset the chip */
	gem_reset(gp);

	/* Make sure ints are disabled */
	gem_disable_ints(gp);

	/* Allocate & setup ring buffers */
	gem_init_rings(gp);

	/* Configure pause thresholds */
	gem_init_pause_thresholds(gp);

	/* Init DMA & MAC engines */
	gem_init_dma(gp);
	gem_init_mac(gp);
}