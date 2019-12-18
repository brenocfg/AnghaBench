#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long* SCMD; int /*<<< orphan*/ * SASR; } ;
typedef  TYPE_1__ wd33c93_regs ;

/* Variables and functions */
 int /*<<< orphan*/  WD_TRANSFER_COUNT_MSB ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void
write_wd33c93_count(const wd33c93_regs regs, unsigned long value)
{
	*regs.SASR = WD_TRANSFER_COUNT_MSB;
	mb();
	*regs.SCMD = value >> 16;
	*regs.SCMD = value >> 8;
	*regs.SCMD = value;
	mb();
}