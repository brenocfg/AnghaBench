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
struct sti_mixer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAM_MIXER_BKC ; 
 int /*<<< orphan*/  sti_mixer_reg_write (struct sti_mixer*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void sti_mixer_set_background_color(struct sti_mixer *mixer,
					   unsigned int rgb)
{
	sti_mixer_reg_write(mixer, GAM_MIXER_BKC, rgb);
}