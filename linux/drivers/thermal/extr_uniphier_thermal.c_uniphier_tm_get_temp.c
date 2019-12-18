#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct uniphier_tm_dev {TYPE_1__* data; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {scalar_t__ map_base; } ;

/* Variables and functions */
 scalar_t__ TMOD ; 
 scalar_t__ TMOD_WIDTH ; 
 int regmap_read (struct regmap*,scalar_t__,int /*<<< orphan*/ *) ; 
 int sign_extend32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int uniphier_tm_get_temp(void *data, int *out_temp)
{
	struct uniphier_tm_dev *tdev = data;
	struct regmap *map = tdev->regmap;
	int ret;
	u32 temp;

	ret = regmap_read(map, tdev->data->map_base + TMOD, &temp);
	if (ret)
		return ret;

	/* MSB of the TMOD field is a sign bit */
	*out_temp = sign_extend32(temp, TMOD_WIDTH - 1) * 1000;

	return 0;
}