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
typedef  int uint64_t ;
typedef  int u64 ;
typedef  size_t u32 ;
struct qca8k_priv {int dummy; } ;
struct qca8k_mib_desc {size_t offset; int size; } ;
struct dsa_switch {scalar_t__ priv; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct qca8k_mib_desc*) ; 
 size_t QCA8K_PORT_MIB_COUNTER (int) ; 
 struct qca8k_mib_desc* ar8327_mib ; 
 int qca8k_read (struct qca8k_priv*,size_t) ; 

__attribute__((used)) static void
qca8k_get_ethtool_stats(struct dsa_switch *ds, int port,
			uint64_t *data)
{
	struct qca8k_priv *priv = (struct qca8k_priv *)ds->priv;
	const struct qca8k_mib_desc *mib;
	u32 reg, i;
	u64 hi;

	for (i = 0; i < ARRAY_SIZE(ar8327_mib); i++) {
		mib = &ar8327_mib[i];
		reg = QCA8K_PORT_MIB_COUNTER(port) + mib->offset;

		data[i] = qca8k_read(priv, reg);
		if (mib->size == 2) {
			hi = qca8k_read(priv, reg + 4);
			data[i] |= hi << 32;
		}
	}
}