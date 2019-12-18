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
struct mv88e6060_priv {scalar_t__ sw_addr; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int mdiobus_write_nested (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reg_write(struct mv88e6060_priv *priv, int addr, int reg, u16 val)
{
	return mdiobus_write_nested(priv->bus, priv->sw_addr + addr, reg, val);
}