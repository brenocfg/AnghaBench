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
 int QCA8K_MIB_BUSY ; 
 int QCA8K_MIB_CPU_KEEP ; 
 int QCA8K_MIB_FLUSH ; 
 int /*<<< orphan*/  QCA8K_MODULE_EN_MIB ; 
 int /*<<< orphan*/  QCA8K_REG_MIB ; 
 int /*<<< orphan*/  QCA8K_REG_MODULE_EN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qca8k_busy_wait (struct qca8k_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qca8k_reg_set (struct qca8k_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qca8k_write (struct qca8k_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qca8k_mib_init(struct qca8k_priv *priv)
{
	mutex_lock(&priv->reg_mutex);
	qca8k_reg_set(priv, QCA8K_REG_MIB, QCA8K_MIB_FLUSH | QCA8K_MIB_BUSY);
	qca8k_busy_wait(priv, QCA8K_REG_MIB, QCA8K_MIB_BUSY);
	qca8k_reg_set(priv, QCA8K_REG_MIB, QCA8K_MIB_CPU_KEEP);
	qca8k_write(priv, QCA8K_REG_MODULE_EN, QCA8K_MODULE_EN_MIB);
	mutex_unlock(&priv->reg_mutex);
}