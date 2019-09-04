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
struct qca8k_priv {int /*<<< orphan*/  reg_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCA8K_FDB_PURGE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qca8k_fdb_access (struct qca8k_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qca8k_fdb_write (struct qca8k_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qca8k_fdb_del(struct qca8k_priv *priv, const u8 *mac, u16 port_mask, u16 vid)
{
	int ret;

	mutex_lock(&priv->reg_mutex);
	qca8k_fdb_write(priv, vid, port_mask, mac, 0);
	ret = qca8k_fdb_access(priv, QCA8K_FDB_PURGE, -1);
	mutex_unlock(&priv->reg_mutex);

	return ret;
}