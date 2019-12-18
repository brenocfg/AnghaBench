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
struct tps65090_platform_data {int dummy; } ;
struct platform_device {int dummy; } ;
struct of_regulator_match {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct tps65090_platform_data *tps65090_parse_dt_reg_data(
			struct platform_device *pdev,
			struct of_regulator_match **tps65090_reg_matches)
{
	*tps65090_reg_matches = NULL;
	return NULL;
}