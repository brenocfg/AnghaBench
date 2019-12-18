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
struct mv88e6060_priv {scalar_t__ sw_addr; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int mdiobus_read_nested (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int reg_read(struct mv88e6060_priv *priv, int addr, int reg)
{
	return mdiobus_read_nested(priv->bus, priv->sw_addr + addr, reg);
}