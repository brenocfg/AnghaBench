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
struct arc_emac_priv {int dummy; } ;

/* Variables and functions */
 unsigned int arc_reg_get (struct arc_emac_priv*,int) ; 
 int /*<<< orphan*/  arc_reg_set (struct arc_emac_priv*,int,unsigned int) ; 

__attribute__((used)) static inline void arc_reg_or(struct arc_emac_priv *priv, int reg, int mask)
{
	unsigned int value = arc_reg_get(priv, reg);

	arc_reg_set(priv, reg, value | mask);
}