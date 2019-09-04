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
struct sudmac_chan {int dint_end_bit; scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ SUDMAC_CH0DEN ; 
 scalar_t__ SUDMAC_DINTCTRL ; 
 scalar_t__ SUDMAC_DINTSTSCLR ; 
 int sudmac_readl (struct sudmac_chan*,scalar_t__) ; 
 int /*<<< orphan*/  sudmac_writel (struct sudmac_chan*,int,scalar_t__) ; 

__attribute__((used)) static inline void sudmac_dma_halt(struct sudmac_chan *sc)
{
	u32 dintctrl = sudmac_readl(sc, SUDMAC_DINTCTRL);

	sudmac_writel(sc, 0, SUDMAC_CH0DEN + sc->offset);
	sudmac_writel(sc, dintctrl & ~sc->dint_end_bit, SUDMAC_DINTCTRL);
	sudmac_writel(sc, sc->dint_end_bit, SUDMAC_DINTSTSCLR);
}