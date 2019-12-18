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
typedef  unsigned int u8 ;
struct rtc7301_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_get_reg_stride (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static u8 rtc7301_read(struct rtc7301_priv *priv, unsigned int reg)
{
	int reg_stride = regmap_get_reg_stride(priv->regmap);
	unsigned int val;

	regmap_read(priv->regmap, reg_stride * reg, &val);

	return val & 0xf;
}