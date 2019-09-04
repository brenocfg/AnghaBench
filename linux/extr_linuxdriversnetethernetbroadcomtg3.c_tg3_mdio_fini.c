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
struct tg3 {int /*<<< orphan*/  mdio_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIOBUS_INITED ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_flag_clear (struct tg3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_mdio_fini(struct tg3 *tp)
{
	if (tg3_flag(tp, MDIOBUS_INITED)) {
		tg3_flag_clear(tp, MDIOBUS_INITED);
		mdiobus_unregister(tp->mdio_bus);
		mdiobus_free(tp->mdio_bus);
	}
}