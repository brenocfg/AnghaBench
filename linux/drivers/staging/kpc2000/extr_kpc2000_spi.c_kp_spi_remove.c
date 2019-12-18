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
struct spi_master {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spi_unregister_master (struct spi_master*) ; 

__attribute__((used)) static int
kp_spi_remove(struct platform_device *pldev)
{
	struct spi_master *master = platform_get_drvdata(pldev);

	spi_unregister_master(master);
	return 0;
}