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
struct TYPE_2__ {int /*<<< orphan*/  func; int /*<<< orphan*/  dev; } ;
union win_slot_encoding {TYPE_1__ bits; int /*<<< orphan*/  slot; } ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wslot_to_devfn(u32 wslot)
{
	union win_slot_encoding slot_no;

	slot_no.slot = wslot;
	return PCI_DEVFN(slot_no.bits.dev, slot_no.bits.func);
}