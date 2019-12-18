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
struct TYPE_3__ {int /*<<< orphan*/  fsci_type; } ;
struct TYPE_4__ {scalar_t__ opcode; TYPE_1__ prot_info; } ;
struct pn533_target_type_b {TYPE_2__ sensb_res; } ;

/* Variables and functions */
 scalar_t__ PN533_TYPE_B_OPC_SENSB_RES ; 
 int PN533_TYPE_B_PROT_TYPE (int /*<<< orphan*/ ) ; 
 int PN533_TYPE_B_PROT_TYPE_RFU_MASK ; 

__attribute__((used)) static bool pn533_target_type_b_is_valid(struct pn533_target_type_b *type_b,
							int target_data_len)
{
	if (target_data_len < sizeof(struct pn533_target_type_b))
		return false;

	if (type_b->sensb_res.opcode != PN533_TYPE_B_OPC_SENSB_RES)
		return false;

	if (PN533_TYPE_B_PROT_TYPE(type_b->sensb_res.prot_info.fsci_type) &
						PN533_TYPE_B_PROT_TYPE_RFU_MASK)
		return false;

	return true;
}