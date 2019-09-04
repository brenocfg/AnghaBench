#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  NewPhysicalDeviceInformationDMA; } ;
struct TYPE_26__ {TYPE_3__ V2; } ;
struct TYPE_22__ {TYPE_4__* ScatterGatherSegments; } ;
struct TYPE_19__ {unsigned char LogicalUnit; unsigned char TargetID; unsigned char Channel; } ;
struct TYPE_18__ {int DataTransferControllerToHost; int NoAutoRequestSense; } ;
struct TYPE_23__ {int DataTransferSize; TYPE_5__ DataTransferMemoryAddress; int /*<<< orphan*/  IOCTL_Opcode; TYPE_2__ PhysicalDevice; TYPE_1__ CommandControlBits; int /*<<< orphan*/  CommandOpcode; } ;
struct TYPE_25__ {TYPE_6__ PhysicalDeviceInfo; } ;
struct TYPE_24__ {scalar_t__ CommandStatus; TYPE_8__ CommandMailbox; } ;
struct TYPE_21__ {int SegmentByteCount; int /*<<< orphan*/  SegmentDataPointer; } ;
struct TYPE_17__ {TYPE_7__ V2; int /*<<< orphan*/  CommandType; } ;
typedef  int /*<<< orphan*/  DAC960_V2_PhysicalDeviceInfo_T ;
typedef  scalar_t__ DAC960_V2_CommandStatus_T ;
typedef  TYPE_8__ DAC960_V2_CommandMailbox_T ;
typedef  TYPE_9__ DAC960_Controller_T ;
typedef  TYPE_10__ DAC960_Command_T ;

/* Variables and functions */
 TYPE_10__* DAC960_AllocateCommand (TYPE_9__*) ; 
 int /*<<< orphan*/  DAC960_DeallocateCommand (TYPE_10__*) ; 
 int /*<<< orphan*/  DAC960_ExecuteCommand (TYPE_10__*) ; 
 int /*<<< orphan*/  DAC960_ImmediateCommand ; 
 int /*<<< orphan*/  DAC960_V2_ClearCommand (TYPE_10__*) ; 
 int /*<<< orphan*/  DAC960_V2_GetPhysicalDeviceInfoValid ; 
 int /*<<< orphan*/  DAC960_V2_IOCTL ; 
 scalar_t__ DAC960_V2_NormalCompletion ; 

__attribute__((used)) static bool DAC960_V2_NewPhysicalDeviceInfo(DAC960_Controller_T *Controller,
					    unsigned char Channel,
					    unsigned char TargetID,
					    unsigned char LogicalUnit)
{
  DAC960_Command_T *Command = DAC960_AllocateCommand(Controller);
  DAC960_V2_CommandMailbox_T *CommandMailbox = &Command->V2.CommandMailbox;
  DAC960_V2_CommandStatus_T CommandStatus;

  DAC960_V2_ClearCommand(Command);
  Command->CommandType = DAC960_ImmediateCommand;
  CommandMailbox->PhysicalDeviceInfo.CommandOpcode = DAC960_V2_IOCTL;
  CommandMailbox->PhysicalDeviceInfo.CommandControlBits
				    .DataTransferControllerToHost = true;
  CommandMailbox->PhysicalDeviceInfo.CommandControlBits
				    .NoAutoRequestSense = true;
  CommandMailbox->PhysicalDeviceInfo.DataTransferSize =
				sizeof(DAC960_V2_PhysicalDeviceInfo_T);
  CommandMailbox->PhysicalDeviceInfo.PhysicalDevice.LogicalUnit = LogicalUnit;
  CommandMailbox->PhysicalDeviceInfo.PhysicalDevice.TargetID = TargetID;
  CommandMailbox->PhysicalDeviceInfo.PhysicalDevice.Channel = Channel;
  CommandMailbox->PhysicalDeviceInfo.IOCTL_Opcode =
					DAC960_V2_GetPhysicalDeviceInfoValid;
  CommandMailbox->PhysicalDeviceInfo.DataTransferMemoryAddress
				    .ScatterGatherSegments[0]
				    .SegmentDataPointer =
    					Controller->V2.NewPhysicalDeviceInformationDMA;
  CommandMailbox->PhysicalDeviceInfo.DataTransferMemoryAddress
				    .ScatterGatherSegments[0]
				    .SegmentByteCount =
    CommandMailbox->PhysicalDeviceInfo.DataTransferSize;
  DAC960_ExecuteCommand(Command);
  CommandStatus = Command->V2.CommandStatus;
  DAC960_DeallocateCommand(Command);
  return (CommandStatus == DAC960_V2_NormalCompletion);
}