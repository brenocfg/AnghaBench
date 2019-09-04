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
struct bh1770_chip {int /*<<< orphan*/  lux_data_raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  bh1770_lux_get_result (struct bh1770_chip*) ; 
 int bh1770_lux_raw_to_adjusted (struct bh1770_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bh1770_lux_read_result(struct bh1770_chip *chip)
{
	bh1770_lux_get_result(chip);
	return bh1770_lux_raw_to_adjusted(chip, chip->lux_data_raw);
}