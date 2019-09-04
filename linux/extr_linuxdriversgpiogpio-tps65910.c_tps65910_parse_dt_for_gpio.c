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
struct tps65910_board {int dummy; } ;
struct tps65910 {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct tps65910_board *tps65910_parse_dt_for_gpio(struct device *dev,
		struct tps65910 *tps65910, int chip_ngpio)
{
	return NULL;
}