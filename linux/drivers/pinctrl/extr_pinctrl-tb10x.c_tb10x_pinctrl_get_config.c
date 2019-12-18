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
struct tb10x_pinctrl {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 unsigned int PCFG_PORT_BITWIDTH ; 
 unsigned int PCFG_PORT_MASK (unsigned int) ; 
 unsigned int ioread32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int tb10x_pinctrl_get_config(
				struct tb10x_pinctrl *state,
				unsigned int port)
{
	return (ioread32(state->base) & PCFG_PORT_MASK(port))
		>> (PCFG_PORT_BITWIDTH * port);
}