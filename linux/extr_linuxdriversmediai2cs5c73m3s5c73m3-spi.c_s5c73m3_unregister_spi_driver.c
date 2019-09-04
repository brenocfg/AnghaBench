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
struct s5c73m3 {int /*<<< orphan*/  spidrv; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_unregister_driver (int /*<<< orphan*/ *) ; 

void s5c73m3_unregister_spi_driver(struct s5c73m3 *state)
{
	spi_unregister_driver(&state->spidrv);
}