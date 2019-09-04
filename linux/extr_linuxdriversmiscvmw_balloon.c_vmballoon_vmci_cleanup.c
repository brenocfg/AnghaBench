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
struct TYPE_2__ {int /*<<< orphan*/  doorbell_unset; } ;
struct vmballoon {int /*<<< orphan*/  vmci_doorbell; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMCI_DOORBELL_SET ; 
 int /*<<< orphan*/  VMCI_INVALID_HANDLE ; 
 int /*<<< orphan*/  VMCI_INVALID_ID ; 
 int /*<<< orphan*/  VMWARE_BALLOON_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmci_doorbell_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_handle_is_invalid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmballoon_vmci_cleanup(struct vmballoon *b)
{
	int error;

	VMWARE_BALLOON_CMD(VMCI_DOORBELL_SET, VMCI_INVALID_ID,
			VMCI_INVALID_ID, error);
	STATS_INC(b->stats.doorbell_unset);

	if (!vmci_handle_is_invalid(b->vmci_doorbell)) {
		vmci_doorbell_destroy(b->vmci_doorbell);
		b->vmci_doorbell = VMCI_INVALID_HANDLE;
	}
}