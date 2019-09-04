#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * Words; } ;
typedef  TYPE_1__ DAC960_V1_CommandMailbox_T ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline
void DAC960_PG_WriteCommandMailbox(DAC960_V1_CommandMailbox_T
				     *MemoryCommandMailbox,
				   DAC960_V1_CommandMailbox_T
				     *CommandMailbox)
{
  MemoryCommandMailbox->Words[1] = CommandMailbox->Words[1];
  MemoryCommandMailbox->Words[2] = CommandMailbox->Words[2];
  MemoryCommandMailbox->Words[3] = CommandMailbox->Words[3];
  wmb();
  MemoryCommandMailbox->Words[0] = CommandMailbox->Words[0];
  mb();
}