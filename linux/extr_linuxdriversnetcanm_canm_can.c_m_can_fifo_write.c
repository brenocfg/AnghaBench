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
typedef  int u32 ;
struct m_can_priv {TYPE_1__* mcfg; scalar_t__ mram_base; } ;
struct TYPE_2__ {scalar_t__ off; } ;

/* Variables and functions */
 size_t MRAM_TXB ; 
 int TXB_ELEMENT_SIZE ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void m_can_fifo_write(const struct m_can_priv *priv,
				    u32 fpi, unsigned int offset, u32 val)
{
	writel(val, priv->mram_base + priv->mcfg[MRAM_TXB].off +
	       fpi * TXB_ELEMENT_SIZE + offset);
}