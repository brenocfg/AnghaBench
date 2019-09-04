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
struct mn {int mnctr_mode_shift; } ;

/* Variables and functions */
 int MNCTR_MODE_MASK ; 

__attribute__((used)) static u32 reg_to_mnctr_mode(struct mn *mn, u32 val)
{
	val >>= mn->mnctr_mode_shift;
	val &= MNCTR_MODE_MASK;
	return val;
}