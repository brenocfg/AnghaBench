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
struct ksz_device {int dummy; } ;
struct dsa_switch {struct ksz_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SW_VLAN_ENABLE ; 
 int /*<<< orphan*/  S_MIRROR_CTRL ; 
 int /*<<< orphan*/  ksz_cfg (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ksz8795_port_vlan_filtering(struct dsa_switch *ds, int port,
				       bool flag)
{
	struct ksz_device *dev = ds->priv;

	ksz_cfg(dev, S_MIRROR_CTRL, SW_VLAN_ENABLE, flag);

	return 0;
}