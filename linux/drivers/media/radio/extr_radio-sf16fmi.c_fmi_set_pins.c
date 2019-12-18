#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct fmi {int /*<<< orphan*/  lock; int /*<<< orphan*/  io; int /*<<< orphan*/  mute; } ;

/* Variables and functions */
 int FMI_BIT_TUN_CE ; 
 int FMI_BIT_TUN_CLK ; 
 int FMI_BIT_TUN_DATA ; 
 int FMI_BIT_TUN_STRQ ; 
 int FMI_BIT_VOL_SW ; 
 int LM7000_CE ; 
 int LM7000_CLK ; 
 int LM7000_DATA ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fmi_set_pins(void *handle, u8 pins)
{
	struct fmi *fmi = handle;
	u8 bits = FMI_BIT_TUN_STRQ;

	if (!fmi->mute)
		bits |= FMI_BIT_VOL_SW;

	if (pins & LM7000_DATA)
		bits |= FMI_BIT_TUN_DATA;
	if (pins & LM7000_CLK)
		bits |= FMI_BIT_TUN_CLK;
	if (pins & LM7000_CE)
		bits |= FMI_BIT_TUN_CE;

	mutex_lock(&fmi->lock);
	outb_p(bits, fmi->io);
	mutex_unlock(&fmi->lock);
}