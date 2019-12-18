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
struct ntb_msi_desc {scalar_t__ addr_offset; } ;
struct ntb_dev {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int ntb_peer_mw_count (struct ntb_dev*) ; 
 int ntb_peer_mw_get_addr (struct ntb_dev*,int,scalar_t__*,int /*<<< orphan*/ *) ; 

int ntb_msi_peer_addr(struct ntb_dev *ntb, int peer,
		      struct ntb_msi_desc *desc,
		      phys_addr_t *msi_addr)
{
	int peer_widx = ntb_peer_mw_count(ntb) - 1 - peer;
	phys_addr_t mw_phys_addr;
	int ret;

	ret = ntb_peer_mw_get_addr(ntb, peer_widx, &mw_phys_addr, NULL);
	if (ret)
		return ret;

	if (msi_addr)
		*msi_addr = mw_phys_addr + desc->addr_offset;

	return 0;
}