#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct mpc52xx_sdma {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ofnode; int /*<<< orphan*/  regs_base; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 TYPE_1__* bcom_eng ; 
 int /*<<< orphan*/  bcom_engine_cleanup () ; 
 int /*<<< orphan*/  bcom_sram_cleanup () ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mpc52xx_bcom_remove(struct platform_device *op)
{
	/* Clean up the engine */
	bcom_engine_cleanup();

	/* Cleanup SRAM */
	bcom_sram_cleanup();

	/* Release regs */
	iounmap(bcom_eng->regs);
	release_mem_region(bcom_eng->regs_base, sizeof(struct mpc52xx_sdma));

	/* Release the node */
	of_node_put(bcom_eng->ofnode);

	/* Release memory */
	kfree(bcom_eng);
	bcom_eng = NULL;

	return 0;
}