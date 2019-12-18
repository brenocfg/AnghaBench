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
typedef  int /*<<< orphan*/  uint16_t ;
struct spi_engine_program {size_t length; int /*<<< orphan*/ * instructions; } ;

/* Variables and functions */

__attribute__((used)) static void spi_engine_program_add_cmd(struct spi_engine_program *p,
	bool dry, uint16_t cmd)
{
	if (!dry)
		p->instructions[p->length] = cmd;
	p->length++;
}