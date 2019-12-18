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
struct TYPE_5__ {int FifoEmptyCount; int /*<<< orphan*/ * PGRAPH; TYPE_1__* Rop; } ;
struct TYPE_4__ {int /*<<< orphan*/  FifoFree; } ;
typedef  TYPE_2__ RIVA_HW_INST ;

/* Variables and functions */
 int NV_RD32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nv4Busy
(
    RIVA_HW_INST *chip
)
{
    return ((NV_RD32(&chip->Rop->FifoFree, 0) < chip->FifoEmptyCount) ||
	    NV_RD32(&chip->PGRAPH[0x00000700/4], 0) & 0x01);
}