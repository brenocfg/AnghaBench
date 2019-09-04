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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct qca8k_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCA8K_ATU_STATUS_STATIC ; 
 int qca8k_fdb_add (struct qca8k_priv*,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qca8k_port_fdb_insert(struct qca8k_priv *priv, const u8 *addr,
		      u16 port_mask, u16 vid)
{
	/* Set the vid to the port vlan id if no vid is set */
	if (!vid)
		vid = 1;

	return qca8k_fdb_add(priv, addr, port_mask, vid,
			     QCA8K_ATU_STATUS_STATIC);
}