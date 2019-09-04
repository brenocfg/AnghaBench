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
 size_t MRAM_RXF0 ; 
 int RXF0_ELEMENT_SIZE ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static inline u32 m_can_fifo_read(const struct m_can_priv *priv,
				  u32 fgi, unsigned int offset)
{
	return readl(priv->mram_base + priv->mcfg[MRAM_RXF0].off +
		     fgi * RXF0_ELEMENT_SIZE + offset);
}