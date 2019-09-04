#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct request {int dummy; } ;
struct TYPE_6__ {size_t LogicalDriveNumber; scalar_t__ DmaDirection; int SegmentCount; int BlockCount; int /*<<< orphan*/  BlockNumber; int /*<<< orphan*/  cmd_sglist; struct request* Request; int /*<<< orphan*/  CommandType; TYPE_1__* Controller; } ;
struct TYPE_5__ {int /*<<< orphan*/  PCIDevice; struct request_queue** RequestQueue; } ;
typedef  TYPE_1__ DAC960_Controller_T ;
typedef  TYPE_2__ DAC960_Command_T ;

/* Variables and functions */
 int /*<<< orphan*/  DAC960_QueueReadWriteCommand (TYPE_2__*) ; 
 int /*<<< orphan*/  DAC960_ReadRetryCommand ; 
 int /*<<< orphan*/  DAC960_WriteRetryCommand ; 
 scalar_t__ PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  blk_rq_map_sg (struct request_queue*,struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 int /*<<< orphan*/  pci_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static void DAC960_queue_partial_rw(DAC960_Command_T *Command)
{
  DAC960_Controller_T *Controller = Command->Controller;
  struct request *Request = Command->Request;
  struct request_queue *req_q = Controller->RequestQueue[Command->LogicalDriveNumber];

  if (Command->DmaDirection == PCI_DMA_FROMDEVICE)
    Command->CommandType = DAC960_ReadRetryCommand;
  else
    Command->CommandType = DAC960_WriteRetryCommand;

  /*
   * We could be more efficient with these mapping requests
   * and map only the portions that we need.  But since this
   * code should almost never be called, just go with a
   * simple coding.
   */
  (void)blk_rq_map_sg(req_q, Command->Request, Command->cmd_sglist);

  (void)pci_map_sg(Controller->PCIDevice, Command->cmd_sglist, 1, Command->DmaDirection);
  /*
   * Resubmitting the request sector at a time is really tedious.
   * But, this should almost never happen.  So, we're willing to pay
   * this price so that in the end, as much of the transfer is completed
   * successfully as possible.
   */
  Command->SegmentCount = 1;
  Command->BlockNumber = blk_rq_pos(Request);
  Command->BlockCount = 1;
  DAC960_QueueReadWriteCommand(Command);
  return;
}