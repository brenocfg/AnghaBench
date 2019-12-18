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
struct TYPE_2__ {int /*<<< orphan*/  quad_enable; } ;
struct spi_nor {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  macronix_quad_enable ; 

__attribute__((used)) static void gd25q256_default_init(struct spi_nor *nor)
{
	/*
	 * Some manufacturer like GigaDevice may use different
	 * bit to set QE on different memories, so the MFR can't
	 * indicate the quad_enable method for this case, we need
	 * to set it in the default_init fixup hook.
	 */
	nor->params.quad_enable = macronix_quad_enable;
}