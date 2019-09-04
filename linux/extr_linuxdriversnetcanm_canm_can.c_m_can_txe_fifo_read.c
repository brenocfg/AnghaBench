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
struct m_can_priv {int mram_base; TYPE_1__* mcfg; } ;
struct TYPE_2__ {int off; } ;

/* Variables and functions */
 size_t MRAM_TXE ; 
 int TXE_ELEMENT_SIZE ; 
 int readl (int) ; 

__attribute__((used)) static inline u32 m_can_txe_fifo_read(const struct m_can_priv *priv,
				      u32 fgi,
				      u32 offset) {
	return readl(priv->mram_base + priv->mcfg[MRAM_TXE].off +
			fgi * TXE_ELEMENT_SIZE + offset);
}