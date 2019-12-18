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
struct cphy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  simple_mdio_read (struct cphy*,int,int*) ; 
 int /*<<< orphan*/  simple_mdio_write (struct cphy*,int,int) ; 

__attribute__((used)) static void mdio_clear_bit(struct cphy *cphy, int reg, u32 bitval)
{
	u32 val;

	(void) simple_mdio_read(cphy, reg, &val);
	(void) simple_mdio_write(cphy, reg, val & ~bitval);
}