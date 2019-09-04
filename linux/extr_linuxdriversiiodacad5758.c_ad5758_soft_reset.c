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
struct ad5758_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5758_KEY ; 
 int /*<<< orphan*/  AD5758_KEY_CODE_RESET_1 ; 
 int /*<<< orphan*/  AD5758_KEY_CODE_RESET_2 ; 
 int ad5758_spi_reg_write (struct ad5758_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ad5758_soft_reset(struct ad5758_state *st)
{
	int ret;

	ret = ad5758_spi_reg_write(st, AD5758_KEY, AD5758_KEY_CODE_RESET_1);
	if (ret < 0)
		return ret;

	ret = ad5758_spi_reg_write(st, AD5758_KEY, AD5758_KEY_CODE_RESET_2);

	/* Perform a software reset and wait at least 100us */
	usleep_range(100, 1000);

	return ret;
}