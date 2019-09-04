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
typedef  int /*<<< orphan*/  u16 ;
struct mt7530_priv {int /*<<< orphan*/  reg_mutex; } ;
struct dsa_switch {struct mt7530_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  MT7530_FDB_WRITE ; 
 int /*<<< orphan*/  STATIC_ENT ; 
 int mt7530_fdb_cmd (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt7530_fdb_write (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt7530_port_fdb_add(struct dsa_switch *ds, int port,
		    const unsigned char *addr, u16 vid)
{
	struct mt7530_priv *priv = ds->priv;
	int ret;
	u8 port_mask = BIT(port);

	mutex_lock(&priv->reg_mutex);
	mt7530_fdb_write(priv, vid, port_mask, addr, -1, STATIC_ENT);
	ret = mt7530_fdb_cmd(priv, MT7530_FDB_WRITE, NULL);
	mutex_unlock(&priv->reg_mutex);

	return ret;
}