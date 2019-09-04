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
struct m_can_priv {int base; } ;
typedef  enum m_can_reg { ____Placeholder_m_can_reg } m_can_reg ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void m_can_write(const struct m_can_priv *priv,
			       enum m_can_reg reg, u32 val)
{
	writel(val, priv->base + reg);
}