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
struct spi_device {int chip_select; int /*<<< orphan*/  master; } ;
struct sc18is602 {scalar_t__ id; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ sc18is602 ; 
 struct sc18is602* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sc18is602_setup(struct spi_device *spi)
{
	struct sc18is602 *hw = spi_master_get_devdata(spi->master);

	/* SC18IS602 does not support CS2 */
	if (hw->id == sc18is602 && spi->chip_select == 2)
		return -ENXIO;

	return 0;
}