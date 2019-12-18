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
typedef  int /*<<< orphan*/  u16 ;
struct iavf_aq_desc {void* flags; void* opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_AQ_FLAG_SI ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void iavf_fill_default_direct_cmd_desc(struct iavf_aq_desc *desc, u16 opcode)
{
	/* zero out the desc */
	memset((void *)desc, 0, sizeof(struct iavf_aq_desc));
	desc->opcode = cpu_to_le16(opcode);
	desc->flags = cpu_to_le16(IAVF_AQ_FLAG_SI);
}