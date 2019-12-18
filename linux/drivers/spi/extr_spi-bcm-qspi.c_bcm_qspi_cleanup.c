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
struct bcm_qspi_parms {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct bcm_qspi_parms*) ; 
 struct bcm_qspi_parms* spi_get_ctldata (struct spi_device*) ; 

__attribute__((used)) static void bcm_qspi_cleanup(struct spi_device *spi)
{
	struct bcm_qspi_parms *xp = spi_get_ctldata(spi);

	kfree(xp);
}