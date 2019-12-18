#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ time64_t ;
struct TYPE_19__ {void* parameter_count; } ;
struct TYPE_17__ {TYPE_2__* sgl; } ;
struct TYPE_18__ {TYPE_3__ param; } ;
struct TYPE_22__ {int request_id; TYPE_5__ byte6_offset; int /*<<< orphan*/  size; TYPE_4__ byte8_offset; int /*<<< orphan*/  opcode__sgloffset; } ;
struct TYPE_21__ {int* generic_buffer_phys; int /*<<< orphan*/ ** srb; scalar_t__* generic_buffer_virt; TYPE_6__** command_packet_virt; } ;
struct TYPE_15__ {TYPE_9__ oldcommand; } ;
struct TYPE_20__ {int /*<<< orphan*/  data; void* parameter_size_bytes; void* parameter_id; void* table_id; TYPE_1__ command; } ;
struct TYPE_16__ {void* length; void* address; } ;
struct TYPE_14__ {int tz_minuteswest; } ;
typedef  TYPE_6__ TW_Param_Apache ;
typedef  TYPE_7__ TW_Device_Extension ;
typedef  TYPE_6__ TW_Command_Full ;
typedef  TYPE_9__ TW_Command ;

/* Variables and functions */
 int /*<<< orphan*/  TW_COMMAND_SIZE ; 
 void* TW_CPU_TO_SGL (int) ; 
 int /*<<< orphan*/  TW_OPSGL_IN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TW_OP_SET_PARAM ; 
 int TW_SECTOR_SIZE ; 
 int TW_TIMEKEEP_TABLE ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div_u64_rem (scalar_t__,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 TYPE_12__ sys_tz ; 
 int /*<<< orphan*/  twl_post_command_packet (TYPE_7__*,int) ; 

__attribute__((used)) static void twl_aen_sync_time(TW_Device_Extension *tw_dev, int request_id)
{
	u32 schedulertime;
	TW_Command_Full *full_command_packet;
	TW_Command *command_packet;
	TW_Param_Apache *param;
	time64_t local_time;

	/* Fill out the command packet */
	full_command_packet = tw_dev->command_packet_virt[request_id];
	memset(full_command_packet, 0, sizeof(TW_Command_Full));
	command_packet = &full_command_packet->command.oldcommand;
	command_packet->opcode__sgloffset = TW_OPSGL_IN(2, TW_OP_SET_PARAM);
	command_packet->request_id = request_id;
	command_packet->byte8_offset.param.sgl[0].address = TW_CPU_TO_SGL(tw_dev->generic_buffer_phys[request_id]);
	command_packet->byte8_offset.param.sgl[0].length = TW_CPU_TO_SGL(TW_SECTOR_SIZE);
	command_packet->size = TW_COMMAND_SIZE;
	command_packet->byte6_offset.parameter_count = cpu_to_le16(1);

	/* Setup the param */
	param = (TW_Param_Apache *)tw_dev->generic_buffer_virt[request_id];
	memset(param, 0, TW_SECTOR_SIZE);
	param->table_id = cpu_to_le16(TW_TIMEKEEP_TABLE | 0x8000); /* Controller time keep table */
	param->parameter_id = cpu_to_le16(0x3); /* SchedulerTime */
	param->parameter_size_bytes = cpu_to_le16(4);

	/* Convert system time in UTC to local time seconds since last 
           Sunday 12:00AM */
	local_time = (ktime_get_real_seconds() - (sys_tz.tz_minuteswest * 60));
	div_u64_rem(local_time - (3 * 86400), 604800, &schedulertime);
	schedulertime = cpu_to_le32(schedulertime);

	memcpy(param->data, &schedulertime, sizeof(u32));

	/* Mark internal command */
	tw_dev->srb[request_id] = NULL;

	/* Now post the command */
	twl_post_command_packet(tw_dev, request_id);
}