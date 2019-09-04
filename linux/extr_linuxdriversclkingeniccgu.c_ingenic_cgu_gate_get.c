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
struct ingenic_cgu_gate_info {int clear_to_gate; int /*<<< orphan*/  bit; scalar_t__ reg; } ;
struct ingenic_cgu {scalar_t__ base; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static inline bool
ingenic_cgu_gate_get(struct ingenic_cgu *cgu,
		     const struct ingenic_cgu_gate_info *info)
{
	return !!(readl(cgu->base + info->reg) & BIT(info->bit))
		^ info->clear_to_gate;
}