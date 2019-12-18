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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM355EVM_MSP_COMMAND ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,int) ; 
 int dm355evm_msp_write (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* msp430 ; 

__attribute__((used)) static void dm355evm_command(unsigned command)
{
	int status;

	status = dm355evm_msp_write(command, DM355EVM_MSP_COMMAND);
	if (status < 0)
		dev_err(&msp430->dev, "command %d failure %d\n",
				command, status);
}