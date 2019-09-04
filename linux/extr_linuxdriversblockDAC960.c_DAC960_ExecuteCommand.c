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
struct TYPE_6__ {int /*<<< orphan*/ * Completion; TYPE_1__* Controller; } ;
struct TYPE_5__ {int /*<<< orphan*/  queue_lock; } ;
typedef  TYPE_1__ DAC960_Controller_T ;
typedef  TYPE_2__ DAC960_Command_T ;

/* Variables and functions */
 int /*<<< orphan*/  Completion ; 
 int /*<<< orphan*/  DAC960_QueueCommand (TYPE_2__*) ; 
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DAC960_ExecuteCommand(DAC960_Command_T *Command)
{
  DAC960_Controller_T *Controller = Command->Controller;
  DECLARE_COMPLETION_ONSTACK(Completion);
  unsigned long flags;
  Command->Completion = &Completion;

  spin_lock_irqsave(&Controller->queue_lock, flags);
  DAC960_QueueCommand(Command);
  spin_unlock_irqrestore(&Controller->queue_lock, flags);
 
  if (in_interrupt())
	  return;
  wait_for_completion(&Completion);
}