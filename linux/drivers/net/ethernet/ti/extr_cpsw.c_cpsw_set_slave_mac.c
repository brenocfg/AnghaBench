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
struct cpsw_slave {int dummy; } ;
struct cpsw_priv {int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_HI ; 
 int /*<<< orphan*/  SA_LO ; 
 int /*<<< orphan*/  mac_hi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_lo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slave_write (struct cpsw_slave*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpsw_set_slave_mac(struct cpsw_slave *slave,
			       struct cpsw_priv *priv)
{
	slave_write(slave, mac_hi(priv->mac_addr), SA_HI);
	slave_write(slave, mac_lo(priv->mac_addr), SA_LO);
}