#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct map_info {scalar_t__ map_priv_1; scalar_t__ virt; } ;
struct TYPE_3__ {int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ map_word ;

/* Variables and functions */
 scalar_t__ LTQ_NOR_PROBING ; 
 int /*<<< orphan*/  ebu_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
ltq_write16(struct map_info *map, map_word d, unsigned long adr)
{
	unsigned long flags;

	if (map->map_priv_1 == LTQ_NOR_PROBING)
		adr ^= 2;
	spin_lock_irqsave(&ebu_lock, flags);
	*(u16 *)(map->virt + adr) = d.x[0];
	spin_unlock_irqrestore(&ebu_lock, flags);
}