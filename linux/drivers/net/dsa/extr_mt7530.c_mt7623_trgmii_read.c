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
typedef  int u32 ;
struct mt7530_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  ethernet; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRGMII_BASE (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static u32
mt7623_trgmii_read(struct mt7530_priv *priv, u32 reg)
{
	int ret;
	u32 val;

	ret = regmap_read(priv->ethernet, TRGMII_BASE(reg), &val);
	if (ret < 0) {
		dev_err(priv->dev,
			"failed to priv read register\n");
		return ret;
	}

	return val;
}