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
typedef  int /*<<< orphan*/  u16 ;
struct npcm_pspi {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ NPCM_PSPI_CTL1 ; 
 int /*<<< orphan*/  ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void npcm_pspi_irq_enable(struct npcm_pspi *priv, u16 mask)
{
	u16 val;

	val = ioread16(priv->base + NPCM_PSPI_CTL1);
	val |= mask;
	iowrite16(val, priv->base + NPCM_PSPI_CTL1);
}