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
struct tcan4x5x_priv {scalar_t__ reg_offset; int /*<<< orphan*/  regmap; } ;
struct m_can_classdev {struct tcan4x5x_priv* device_data; } ;

/* Variables and functions */
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int tcan4x5x_write_reg(struct m_can_classdev *cdev, int reg, int val)
{
	struct tcan4x5x_priv *priv = cdev->device_data;

	return regmap_write(priv->regmap, priv->reg_offset + reg, val);
}