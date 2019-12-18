#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int*** virt2phys_pkey; } ;
struct mlx4_ib_dev {TYPE_3__* dev; TYPE_2__ pkeys; } ;
struct TYPE_6__ {int sqp_demux; int* pkey_table_len; } ;
struct TYPE_8__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int mlx4_gen_pkey_eqe (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  mlx4_is_slave_active (TYPE_3__*,int) ; 
 int mlx4_master_func_num (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int) ; 

__attribute__((used)) static void __propagate_pkey_ev(struct mlx4_ib_dev *dev, int port_num,
				int block, u32 change_bitmap)
{
	int i, ix, slave, err;
	int have_event = 0;

	for (slave = 0; slave < dev->dev->caps.sqp_demux; slave++) {
		if (slave == mlx4_master_func_num(dev->dev))
			continue;
		if (!mlx4_is_slave_active(dev->dev, slave))
			continue;

		have_event = 0;
		for (i = 0; i < 32; i++) {
			if (!(change_bitmap & (1 << i)))
				continue;
			for (ix = 0;
			     ix < dev->dev->caps.pkey_table_len[port_num]; ix++) {
				if (dev->pkeys.virt2phys_pkey[slave][port_num - 1]
				    [ix] == i + 32 * block) {
					err = mlx4_gen_pkey_eqe(dev->dev, slave, port_num);
					pr_debug("propagate_pkey_ev: slave %d,"
						 " port %d, ix %d (%d)\n",
						 slave, port_num, ix, err);
					have_event = 1;
					break;
				}
			}
			if (have_event)
				break;
		}
	}
}