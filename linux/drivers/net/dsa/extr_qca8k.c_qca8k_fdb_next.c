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
struct qca8k_priv {int dummy; } ;
struct qca8k_fdb {int /*<<< orphan*/  aging; int /*<<< orphan*/  mac; int /*<<< orphan*/  port_mask; int /*<<< orphan*/  vid; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCA8K_FDB_NEXT ; 
 int qca8k_fdb_access (struct qca8k_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qca8k_fdb_read (struct qca8k_priv*,struct qca8k_fdb*) ; 
 int /*<<< orphan*/  qca8k_fdb_write (struct qca8k_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qca8k_fdb_next(struct qca8k_priv *priv, struct qca8k_fdb *fdb, int port)
{
	int ret;

	qca8k_fdb_write(priv, fdb->vid, fdb->port_mask, fdb->mac, fdb->aging);
	ret = qca8k_fdb_access(priv, QCA8K_FDB_NEXT, port);
	if (ret >= 0)
		qca8k_fdb_read(priv, fdb);

	return ret;
}