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
typedef  int /*<<< orphan*/  u32 ;
struct uniphier_aidet_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned long) ; 
 unsigned long UNIPHIER_AIDET_DETCONF ; 
 int /*<<< orphan*/  uniphier_aidet_reg_update (struct uniphier_aidet_priv*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uniphier_aidet_detconf_update(struct uniphier_aidet_priv *priv,
					  unsigned long index, unsigned int val)
{
	unsigned int reg;
	u32 mask;

	reg = UNIPHIER_AIDET_DETCONF + index / 32 * 4;
	mask = BIT(index % 32);

	uniphier_aidet_reg_update(priv, reg, mask, val ? mask : 0);
}