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
struct ti_hecc_priv {int mbx; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (int,int) ; 

__attribute__((used)) static inline void hecc_write_mbx(struct ti_hecc_priv *priv, u32 mbxno,
				  u32 reg, u32 val)
{
	__raw_writel(val, priv->mbx + mbxno * 0x10 + reg);
}