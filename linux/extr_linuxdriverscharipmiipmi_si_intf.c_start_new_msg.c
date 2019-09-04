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
struct smi_info {int /*<<< orphan*/  si_sm; TYPE_1__* handlers; scalar_t__ thread; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* start_transaction ) (int /*<<< orphan*/ ,unsigned char*,unsigned int) ;} ;

/* Variables and functions */
 scalar_t__ SI_TIMEOUT_JIFFIES ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  smi_mod_timer (struct smi_info*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 

__attribute__((used)) static void start_new_msg(struct smi_info *smi_info, unsigned char *msg,
			  unsigned int size)
{
	smi_mod_timer(smi_info, jiffies + SI_TIMEOUT_JIFFIES);

	if (smi_info->thread)
		wake_up_process(smi_info->thread);

	smi_info->handlers->start_transaction(smi_info->si_sm, msg, size);
}