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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int index; int /*<<< orphan*/  vsp1; } ;
struct vsp1_uif {TYPE_1__ entity; } ;

/* Variables and functions */
 int VI6_UIF_OFFSET ; 
 scalar_t__ vsp1_read (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline u32 vsp1_uif_read(struct vsp1_uif *uif, u32 reg)
{
	return vsp1_read(uif->entity.vsp1,
			 uif->entity.index * VI6_UIF_OFFSET + reg);
}