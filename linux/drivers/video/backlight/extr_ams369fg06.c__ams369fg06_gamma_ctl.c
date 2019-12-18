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
struct ams369fg06 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int GAMMA_TABLE_COUNT ; 
 int ams369fg06_spi_write (struct ams369fg06*,int,unsigned int const) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int _ams369fg06_gamma_ctl(struct ams369fg06 *lcd,
	const unsigned int *gamma)
{
	unsigned int i = 0;
	int ret = 0;

	for (i = 0 ; i < GAMMA_TABLE_COUNT / 3; i++) {
		ret = ams369fg06_spi_write(lcd, 0x40 + i, gamma[i]);
		ret = ams369fg06_spi_write(lcd, 0x50 + i, gamma[i+7*1]);
		ret = ams369fg06_spi_write(lcd, 0x60 + i, gamma[i+7*2]);
		if (ret) {
			dev_err(lcd->dev, "failed to set gamma table.\n");
			goto gamma_err;
		}
	}

gamma_err:
	return ret;
}