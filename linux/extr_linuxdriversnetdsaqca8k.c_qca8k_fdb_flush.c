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
struct qca8k_priv {int /*<<< orphan*/  reg_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCA8K_FDB_FLUSH ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qca8k_fdb_access (struct qca8k_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
qca8k_fdb_flush(struct qca8k_priv *priv)
{
	mutex_lock(&priv->reg_mutex);
	qca8k_fdb_access(priv, QCA8K_FDB_FLUSH, -1);
	mutex_unlock(&priv->reg_mutex);
}