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
struct pasemi_mac {int /*<<< orphan*/  dma_if; } ;

/* Variables and functions */
 unsigned int pasemi_read_mac_reg (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned int read_mac_reg(const struct pasemi_mac *mac, unsigned int reg)
{
	return pasemi_read_mac_reg(mac->dma_if, reg);
}