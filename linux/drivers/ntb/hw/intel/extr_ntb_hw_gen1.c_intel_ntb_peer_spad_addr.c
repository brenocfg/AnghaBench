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
struct ntb_dev {int dummy; } ;
struct intel_ntb_dev {TYPE_1__* peer_reg; int /*<<< orphan*/  peer_addr; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  spad; } ;

/* Variables and functions */
 int ndev_spad_addr (struct intel_ntb_dev*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intel_ntb_dev* ntb_ndev (struct ntb_dev*) ; 

int intel_ntb_peer_spad_addr(struct ntb_dev *ntb, int pidx, int sidx,
			     phys_addr_t *spad_addr)
{
	struct intel_ntb_dev *ndev = ntb_ndev(ntb);

	return ndev_spad_addr(ndev, sidx, spad_addr, ndev->peer_addr,
			      ndev->peer_reg->spad);
}