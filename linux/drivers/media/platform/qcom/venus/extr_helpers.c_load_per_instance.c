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
struct venus_inst {scalar_t__ state; int fps; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ INST_INIT ; 
 scalar_t__ INST_STOP ; 

__attribute__((used)) static u32 load_per_instance(struct venus_inst *inst)
{
	u32 mbs;

	if (!inst || !(inst->state >= INST_INIT && inst->state < INST_STOP))
		return 0;

	mbs = (ALIGN(inst->width, 16) / 16) * (ALIGN(inst->height, 16) / 16);

	return mbs * inst->fps;
}