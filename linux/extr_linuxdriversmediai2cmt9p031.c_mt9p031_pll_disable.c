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
struct mt9p031 {int /*<<< orphan*/  use_pll; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9P031_PLL_CONTROL ; 
 int /*<<< orphan*/  MT9P031_PLL_CONTROL_PWROFF ; 
 int mt9p031_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int mt9p031_pll_disable(struct mt9p031 *mt9p031)
{
	struct i2c_client *client = v4l2_get_subdevdata(&mt9p031->subdev);

	if (!mt9p031->use_pll)
		return 0;

	return mt9p031_write(client, MT9P031_PLL_CONTROL,
			     MT9P031_PLL_CONTROL_PWROFF);
}