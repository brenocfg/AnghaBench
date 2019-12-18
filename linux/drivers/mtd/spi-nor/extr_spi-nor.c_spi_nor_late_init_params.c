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
struct TYPE_2__ {int /*<<< orphan*/ * locking_ops; } ;
struct spi_nor {int flags; TYPE_1__ params; } ;

/* Variables and functions */
 int SNOR_F_HAS_LOCK ; 
 int /*<<< orphan*/  stm_locking_ops ; 

__attribute__((used)) static void spi_nor_late_init_params(struct spi_nor *nor)
{
	/*
	 * NOR protection support. When locking_ops are not provided, we pick
	 * the default ones.
	 */
	if (nor->flags & SNOR_F_HAS_LOCK && !nor->params.locking_ops)
		nor->params.locking_ops = &stm_locking_ops;
}