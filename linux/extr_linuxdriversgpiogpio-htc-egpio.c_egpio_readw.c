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
struct egpio_info {int bus_shift; scalar_t__ base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  readw (scalar_t__) ; 

__attribute__((used)) static inline u16 egpio_readw(struct egpio_info *ei, int reg)
{
	return readw(ei->base_addr + (reg << ei->bus_shift));
}