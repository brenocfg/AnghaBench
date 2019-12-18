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
struct spi_sh_data {int width; scalar_t__ addr; } ;

/* Variables and functions */
 unsigned long ioread32 (scalar_t__) ; 
 unsigned long ioread8 (scalar_t__) ; 

__attribute__((used)) static unsigned long spi_sh_read(struct spi_sh_data *ss, unsigned long offset)
{
	if (ss->width == 8)
		return ioread8(ss->addr + (offset >> 2));
	else if (ss->width == 32)
		return ioread32(ss->addr + offset);
	else
		return 0;
}