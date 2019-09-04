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
struct spi_device {int dummy; } ;
struct cyttsp4 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cyttsp4_remove (struct cyttsp4*) ; 
 struct cyttsp4* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int cyttsp4_spi_remove(struct spi_device *spi)
{
	struct cyttsp4 *ts = spi_get_drvdata(spi);
	cyttsp4_remove(ts);

	return 0;
}