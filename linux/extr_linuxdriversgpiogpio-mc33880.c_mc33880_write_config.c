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
struct mc33880 {int /*<<< orphan*/  port_config; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mc33880_write_config(struct mc33880 *mc)
{
	return spi_write(mc->spi, &mc->port_config, sizeof(mc->port_config));
}