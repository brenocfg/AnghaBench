#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct switchdev_obj_port_mdb {scalar_t__ vid; int /*<<< orphan*/  addr; } ;
struct ksz_device {int num_statics; TYPE_1__* dev_ops; } ;
struct dsa_switch {struct ksz_device* priv; } ;
struct alu_struct {scalar_t__ fid; int is_static; int is_use_fid; int /*<<< orphan*/  port_forward; int /*<<< orphan*/  mac; } ;
typedef  int /*<<< orphan*/  alu ;
struct TYPE_2__ {int /*<<< orphan*/  (* w_sta_mac_table ) (struct ksz_device*,int,struct alu_struct*) ;int /*<<< orphan*/  (* r_sta_mac_table ) (struct ksz_device*,int,struct alu_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct alu_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ksz_device*,int,struct alu_struct*) ; 
 int /*<<< orphan*/  stub2 (struct ksz_device*,int,struct alu_struct*) ; 

void ksz_port_mdb_add(struct dsa_switch *ds, int port,
		      const struct switchdev_obj_port_mdb *mdb)
{
	struct ksz_device *dev = ds->priv;
	struct alu_struct alu;
	int index;
	int empty = 0;

	alu.port_forward = 0;
	for (index = 0; index < dev->num_statics; index++) {
		if (!dev->dev_ops->r_sta_mac_table(dev, index, &alu)) {
			/* Found one already in static MAC table. */
			if (!memcmp(alu.mac, mdb->addr, ETH_ALEN) &&
			    alu.fid == mdb->vid)
				break;
		/* Remember the first empty entry. */
		} else if (!empty) {
			empty = index + 1;
		}
	}

	/* no available entry */
	if (index == dev->num_statics && !empty)
		return;

	/* add entry */
	if (index == dev->num_statics) {
		index = empty - 1;
		memset(&alu, 0, sizeof(alu));
		memcpy(alu.mac, mdb->addr, ETH_ALEN);
		alu.is_static = true;
	}
	alu.port_forward |= BIT(port);
	if (mdb->vid) {
		alu.is_use_fid = true;

		/* Need a way to map VID to FID. */
		alu.fid = mdb->vid;
	}
	dev->dev_ops->w_sta_mac_table(dev, index, &alu);
}