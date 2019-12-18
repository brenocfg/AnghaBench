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
typedef  scalar_t__ u16 ;
struct qtnf_pearl_rx_bd {int dummy; } ;
struct TYPE_2__ {int rx_bd_num; } ;
struct qtnf_pcie_pearl_state {TYPE_1__ base; int /*<<< orphan*/  rx_bd_vbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int pearl_skb2rbd_attach (struct qtnf_pcie_pearl_state*,scalar_t__) ; 

__attribute__((used)) static int pearl_alloc_rx_buffers(struct qtnf_pcie_pearl_state *ps)
{
	u16 i;
	int ret = 0;

	memset(ps->rx_bd_vbase, 0x0,
	       ps->base.rx_bd_num * sizeof(struct qtnf_pearl_rx_bd));

	for (i = 0; i < ps->base.rx_bd_num; i++) {
		ret = pearl_skb2rbd_attach(ps, i);
		if (ret)
			break;
	}

	return ret;
}