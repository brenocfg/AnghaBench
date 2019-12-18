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
typedef  scalar_t__ u32 ;
struct amvdec_core {scalar_t__ dos_base; } ;

/* Variables and functions */
 scalar_t__ readl_relaxed (scalar_t__) ; 

u32 amvdec_read_dos(struct amvdec_core *core, u32 reg)
{
	return readl_relaxed(core->dos_base + reg);
}