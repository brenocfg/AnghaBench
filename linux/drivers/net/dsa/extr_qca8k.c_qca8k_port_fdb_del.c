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
typedef  int u16 ;
struct qca8k_priv {int dummy; } ;
struct dsa_switch {scalar_t__ priv; } ;

/* Variables and functions */
 int BIT (int) ; 
 int qca8k_fdb_del (struct qca8k_priv*,unsigned char const*,int,int) ; 

__attribute__((used)) static int
qca8k_port_fdb_del(struct dsa_switch *ds, int port,
		   const unsigned char *addr, u16 vid)
{
	struct qca8k_priv *priv = (struct qca8k_priv *)ds->priv;
	u16 port_mask = BIT(port);

	if (!vid)
		vid = 1;

	return qca8k_fdb_del(priv, addr, port_mask, vid);
}