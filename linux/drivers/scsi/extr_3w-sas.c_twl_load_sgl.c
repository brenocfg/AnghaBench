#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int dma_addr_t ;
struct TYPE_13__ {int request_id; int size; int /*<<< orphan*/  opcode__sgloffset; } ;
struct TYPE_12__ {void* sgl_entries__lunh; TYPE_1__* sg_list; void* request_id__lunl; int /*<<< orphan*/  opcode__reserved; } ;
struct TYPE_9__ {TYPE_6__ oldcommand; TYPE_5__ newcommand; } ;
struct TYPE_11__ {TYPE_2__ command; } ;
struct TYPE_10__ {void* length; void* address; } ;
struct TYPE_8__ {void* length; void* address; } ;
typedef  TYPE_3__ TW_SG_Entry_ISO ;
typedef  int /*<<< orphan*/  TW_Ioctl_Buf_Apache ;
typedef  int /*<<< orphan*/  TW_Device_Extension ;
typedef  TYPE_4__ TW_Command_Full ;
typedef  TYPE_5__ TW_Command_Apache ;
typedef  TYPE_6__ TW_Command ;

/* Variables and functions */
 void* TW_CPU_TO_SGL (int) ; 
 int /*<<< orphan*/  TW_LUN_OUT (void*) ; 
 scalar_t__ TW_OP_EXECUTE_SCSI ; 
 scalar_t__ TW_OP_OUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TW_REQ_LUN_IN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TW_SGL_OUT (int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void twl_load_sgl(TW_Device_Extension *tw_dev, TW_Command_Full *full_command_packet, int request_id, dma_addr_t dma_handle, int length)
{
	TW_Command *oldcommand;
	TW_Command_Apache *newcommand;
	TW_SG_Entry_ISO *sgl;
	unsigned int pae = 0;

	if ((sizeof(long) < 8) && (sizeof(dma_addr_t) > 4))
		pae = 1;

	if (TW_OP_OUT(full_command_packet->command.newcommand.opcode__reserved) == TW_OP_EXECUTE_SCSI) {
		newcommand = &full_command_packet->command.newcommand;
		newcommand->request_id__lunl =
			cpu_to_le16(TW_REQ_LUN_IN(TW_LUN_OUT(newcommand->request_id__lunl), request_id));
		if (length) {
			newcommand->sg_list[0].address = TW_CPU_TO_SGL(dma_handle + sizeof(TW_Ioctl_Buf_Apache) - 1);
			newcommand->sg_list[0].length = TW_CPU_TO_SGL(length);
		}
		newcommand->sgl_entries__lunh =
			cpu_to_le16(TW_REQ_LUN_IN(TW_LUN_OUT(newcommand->sgl_entries__lunh), length ? 1 : 0));
	} else {
		oldcommand = &full_command_packet->command.oldcommand;
		oldcommand->request_id = request_id;

		if (TW_SGL_OUT(oldcommand->opcode__sgloffset)) {
			/* Load the sg list */
			sgl = (TW_SG_Entry_ISO *)((u32 *)oldcommand+oldcommand->size - (sizeof(TW_SG_Entry_ISO)/4) + pae + (sizeof(dma_addr_t) > 4 ? 1 : 0));
			sgl->address = TW_CPU_TO_SGL(dma_handle + sizeof(TW_Ioctl_Buf_Apache) - 1);
			sgl->length = TW_CPU_TO_SGL(length);
			oldcommand->size += pae;
			oldcommand->size += sizeof(dma_addr_t) > 4 ? 1 : 0;
		}
	}
}