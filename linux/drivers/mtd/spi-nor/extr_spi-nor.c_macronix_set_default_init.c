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
struct TYPE_2__ {int /*<<< orphan*/  set_4byte; int /*<<< orphan*/  quad_enable; } ;
struct spi_nor {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  macronix_quad_enable ; 
 int /*<<< orphan*/  macronix_set_4byte ; 

__attribute__((used)) static void macronix_set_default_init(struct spi_nor *nor)
{
	nor->params.quad_enable = macronix_quad_enable;
	nor->params.set_4byte = macronix_set_4byte;
}