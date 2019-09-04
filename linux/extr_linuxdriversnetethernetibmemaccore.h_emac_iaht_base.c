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
typedef  int /*<<< orphan*/  u32 ;
struct emac_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * emac_xaht_base (struct emac_instance*) ; 

__attribute__((used)) static inline u32 *emac_iaht_base(struct emac_instance *dev)
{
	/* IAHT registers always come before an identical number of
	 * GAHT registers.
	 */
	return emac_xaht_base(dev);
}