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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ CHELSIO_T5 ; 
 int KEYWREN_F ; 
 unsigned int T6_VFWRADDR_M ; 
 int T6_VFWRADDR_V (unsigned int) ; 
 int /*<<< orphan*/  TP_RSS_CONFIG_VRT_A ; 
 int /*<<< orphan*/  TP_RSS_VFH_CONFIG_A ; 
 int /*<<< orphan*/  TP_RSS_VFL_CONFIG_A ; 
 int VFRDEN_F ; 
 int VFRDRG_F ; 
 unsigned int VFWRADDR_M ; 
 int VFWRADDR_V (unsigned int) ; 
 int VFWREN_F ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_tp_pio_read (struct adapter*,int*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

void t4_read_rss_vf_config(struct adapter *adapter, unsigned int index,
			   u32 *vfl, u32 *vfh, bool sleep_ok)
{
	u32 vrt, mask, data;

	if (CHELSIO_CHIP_VERSION(adapter->params.chip) <= CHELSIO_T5) {
		mask = VFWRADDR_V(VFWRADDR_M);
		data = VFWRADDR_V(index);
	} else {
		 mask =  T6_VFWRADDR_V(T6_VFWRADDR_M);
		 data = T6_VFWRADDR_V(index);
	}

	/* Request that the index'th VF Table values be read into VFL/VFH.
	 */
	vrt = t4_read_reg(adapter, TP_RSS_CONFIG_VRT_A);
	vrt &= ~(VFRDRG_F | VFWREN_F | KEYWREN_F | mask);
	vrt |= data | VFRDEN_F;
	t4_write_reg(adapter, TP_RSS_CONFIG_VRT_A, vrt);

	/* Grab the VFL/VFH values ...
	 */
	t4_tp_pio_read(adapter, vfl, 1, TP_RSS_VFL_CONFIG_A, sleep_ok);
	t4_tp_pio_read(adapter, vfh, 1, TP_RSS_VFH_CONFIG_A, sleep_ok);
}