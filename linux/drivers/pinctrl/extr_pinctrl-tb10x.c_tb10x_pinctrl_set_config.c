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
typedef  unsigned int u32 ;
struct tb10x_pinctrl {int /*<<< orphan*/  base; TYPE_1__* ports; } ;
struct TYPE_2__ {unsigned int mode; scalar_t__ count; } ;

/* Variables and functions */
 unsigned int PCFG_PORT_BITWIDTH ; 
 unsigned int PCFG_PORT_MASK (unsigned int) ; 
 unsigned int ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tb10x_pinctrl_set_config(struct tb10x_pinctrl *state,
				unsigned int port, unsigned int mode)
{
	u32 pcfg;

	if (state->ports[port].count)
		return;

	state->ports[port].mode = mode;

	pcfg = ioread32(state->base) & ~(PCFG_PORT_MASK(port));
	pcfg |= (mode << (PCFG_PORT_BITWIDTH * port)) & PCFG_PORT_MASK(port);
	iowrite32(pcfg, state->base);
}