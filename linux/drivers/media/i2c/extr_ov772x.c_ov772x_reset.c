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
struct ov772x_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  COM2 ; 
 int /*<<< orphan*/  COM7 ; 
 int /*<<< orphan*/  SCCB_RESET ; 
 int /*<<< orphan*/  SOFT_SLEEP_MODE ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ov772x_reset(struct ov772x_priv *priv)
{
	int ret;

	ret = regmap_write(priv->regmap, COM7, SCCB_RESET);
	if (ret < 0)
		return ret;

	usleep_range(1000, 5000);

	return regmap_update_bits(priv->regmap, COM2, SOFT_SLEEP_MODE,
				  SOFT_SLEEP_MODE);
}