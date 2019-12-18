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
struct slot {TYPE_1__* zdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; int /*<<< orphan*/  fid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZPCI_FN_STATE_CONFIGURED ; 
 int sclp_pci_configure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpci_dbg (int,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int slot_configure(struct slot *slot)
{
	int ret = sclp_pci_configure(slot->zdev->fid);

	zpci_dbg(3, "conf fid:%x, rc:%d\n", slot->zdev->fid, ret);
	if (!ret)
		slot->zdev->state = ZPCI_FN_STATE_CONFIGURED;

	return ret;
}