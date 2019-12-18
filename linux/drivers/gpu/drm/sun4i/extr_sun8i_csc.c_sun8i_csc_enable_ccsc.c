#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  regs; } ;
struct sun8i_mixer {TYPE_2__ engine; TYPE_1__* cfg; } ;
struct TYPE_3__ {size_t ccsc; scalar_t__ is_de3; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** ccsc_base ; 
 int /*<<< orphan*/  sun8i_csc_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sun8i_de3_ccsc_enable (int /*<<< orphan*/ ,int,int) ; 

void sun8i_csc_enable_ccsc(struct sun8i_mixer *mixer, int layer, bool enable)
{
	u32 base;

	if (mixer->cfg->is_de3) {
		sun8i_de3_ccsc_enable(mixer->engine.regs, layer, enable);
		return;
	}

	base = ccsc_base[mixer->cfg->ccsc][layer];

	sun8i_csc_enable(mixer->engine.regs, base, enable);
}