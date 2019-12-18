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
typedef  int /*<<< orphan*/  u16 ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int spi_write (struct spi_device*,void const*,int) ; 

__attribute__((used)) static int max5487_write_cmd(struct spi_device *spi, u16 cmd)
{
	return spi_write(spi, (const void *) &cmd, sizeof(u16));
}