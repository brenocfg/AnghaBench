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
struct tdo24m {int dummy; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 struct tdo24m* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  tdo24m_power (struct tdo24m*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tdo24m_remove(struct spi_device *spi)
{
	struct tdo24m *lcd = spi_get_drvdata(spi);

	tdo24m_power(lcd, FB_BLANK_POWERDOWN);
	return 0;
}