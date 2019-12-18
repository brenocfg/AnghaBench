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
struct spi_bitbang {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_unregister_master (int /*<<< orphan*/ ) ; 

void spi_bitbang_stop(struct spi_bitbang *bitbang)
{
	spi_unregister_master(bitbang->master);
}