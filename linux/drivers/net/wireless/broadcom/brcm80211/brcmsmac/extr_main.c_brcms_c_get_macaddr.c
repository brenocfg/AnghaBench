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
typedef  int /*<<< orphan*/  u8 ;
struct ssb_sprom {int /*<<< orphan*/  il0mac; int /*<<< orphan*/  et1mac; } ;
struct brcms_hardware {int _nbands; TYPE_2__* d11core; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {struct ssb_sprom sprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcms_c_get_macaddr(struct brcms_hardware *wlc_hw, u8 etheraddr[ETH_ALEN])
{
	struct ssb_sprom *sprom = &wlc_hw->d11core->bus->sprom;

	/* If macaddr exists, use it (Sromrev4, CIS, ...). */
	if (!is_zero_ether_addr(sprom->il0mac)) {
		memcpy(etheraddr, sprom->il0mac, ETH_ALEN);
		return;
	}

	if (wlc_hw->_nbands > 1)
		memcpy(etheraddr, sprom->et1mac, ETH_ALEN);
	else
		memcpy(etheraddr, sprom->il0mac, ETH_ALEN);
}