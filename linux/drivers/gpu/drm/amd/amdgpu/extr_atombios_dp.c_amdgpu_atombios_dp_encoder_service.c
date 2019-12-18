#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void* u8 ;
struct TYPE_4__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_5__ {int ucLinkClock; int ucAction; void* ucStatus; void* ucLaneNum; void* ucConfig; } ;
typedef  TYPE_2__ DP_ENCODER_SERVICE_PARAMETERS ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DPEncoderService ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 amdgpu_atombios_dp_encoder_service(struct amdgpu_device *adev,
				      int action, int dp_clock,
				      u8 ucconfig, u8 lane_num)
{
	DP_ENCODER_SERVICE_PARAMETERS args;
	int index = GetIndexIntoMasterTable(COMMAND, DPEncoderService);

	memset(&args, 0, sizeof(args));
	args.ucLinkClock = dp_clock / 10;
	args.ucConfig = ucconfig;
	args.ucAction = action;
	args.ucLaneNum = lane_num;
	args.ucStatus = 0;

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uint32_t *)&args);
	return args.ucStatus;
}