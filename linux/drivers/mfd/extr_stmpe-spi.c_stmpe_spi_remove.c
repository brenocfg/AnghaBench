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
struct stmpe {int dummy; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 struct stmpe* spi_get_drvdata (struct spi_device*) ; 
 int stmpe_remove (struct stmpe*) ; 

__attribute__((used)) static int stmpe_spi_remove(struct spi_device *spi)
{
	struct stmpe *stmpe = spi_get_drvdata(spi);

	return stmpe_remove(stmpe);
}