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
typedef  int u32 ;
struct sti_mixer {int dummy; } ;

/* Variables and functions */
 int GAM_CTL_BACK_MASK ; 
 int /*<<< orphan*/  GAM_MIXER_CTL ; 
 int sti_mixer_reg_read (struct sti_mixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sti_mixer_reg_write (struct sti_mixer*,int /*<<< orphan*/ ,int) ; 

void sti_mixer_set_background_status(struct sti_mixer *mixer, bool enable)
{
	u32 val = sti_mixer_reg_read(mixer, GAM_MIXER_CTL);

	val &= ~GAM_CTL_BACK_MASK;
	val |= enable;
	sti_mixer_reg_write(mixer, GAM_MIXER_CTL, val);
}