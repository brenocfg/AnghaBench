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
struct TYPE_4__ {int /*<<< orphan*/  PVIO; } ;
typedef  TYPE_1__ RIVA_HW_INST ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_WR08 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vgaLockUnlock (TYPE_1__*,int) ; 

__attribute__((used)) static void nv3LockUnlock
(
    RIVA_HW_INST *chip,
    int           Lock
)
{
    VGA_WR08(chip->PVIO, 0x3C4, 0x06);
    VGA_WR08(chip->PVIO, 0x3C5, Lock ? 0x99 : 0x57);
    vgaLockUnlock(chip, Lock);
}