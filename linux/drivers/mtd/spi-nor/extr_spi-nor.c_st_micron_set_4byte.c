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
struct spi_nor {int dummy; } ;

/* Variables and functions */
 int macronix_set_4byte (struct spi_nor*,int) ; 
 int /*<<< orphan*/  write_disable (struct spi_nor*) ; 
 int /*<<< orphan*/  write_enable (struct spi_nor*) ; 

__attribute__((used)) static int st_micron_set_4byte(struct spi_nor *nor, bool enable)
{
	int ret;

	write_enable(nor);
	ret = macronix_set_4byte(nor, enable);
	write_disable(nor);

	return ret;
}