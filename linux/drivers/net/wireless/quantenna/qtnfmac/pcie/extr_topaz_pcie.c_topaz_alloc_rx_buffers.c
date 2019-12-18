#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct qtnf_topaz_rx_bd {int dummy; } ;
struct TYPE_3__ {int rx_bd_num; } ;
struct qtnf_pcie_topaz_state {TYPE_1__ base; TYPE_2__* rx_bd_vbase; } ;
struct TYPE_4__ {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  QTN_BD_WRAP ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 int topaz_skb2rbd_attach (struct qtnf_pcie_topaz_state*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int topaz_alloc_rx_buffers(struct qtnf_pcie_topaz_state *ts)
{
	u16 i;
	int ret = 0;

	memset(ts->rx_bd_vbase, 0x0,
	       ts->base.rx_bd_num * sizeof(struct qtnf_topaz_rx_bd));

	for (i = 0; i < ts->base.rx_bd_num; i++) {
		ret = topaz_skb2rbd_attach(ts, i, 0);
		if (ret)
			break;
	}

	ts->rx_bd_vbase[ts->base.rx_bd_num - 1].info |=
						cpu_to_le32(QTN_BD_WRAP);

	return ret;
}