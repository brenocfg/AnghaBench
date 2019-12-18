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
struct vme_bridge {struct ca91cx42_driver* driver_priv; } ;
struct ca91cx42_driver {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__* CA91CX42_V_STATID ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  vme_irq_handler (struct vme_bridge*,int,int) ; 

__attribute__((used)) static u32 ca91cx42_VIRQ_irqhandler(struct vme_bridge *ca91cx42_bridge,
	int stat)
{
	int vec, i, serviced = 0;
	struct ca91cx42_driver *bridge;

	bridge = ca91cx42_bridge->driver_priv;


	for (i = 7; i > 0; i--) {
		if (stat & (1 << i)) {
			vec = ioread32(bridge->base +
				CA91CX42_V_STATID[i]) & 0xff;

			vme_irq_handler(ca91cx42_bridge, i, vec);

			serviced |= (1 << i);
		}
	}

	return serviced;
}