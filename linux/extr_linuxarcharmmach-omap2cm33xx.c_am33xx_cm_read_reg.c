#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ va; } ;

/* Variables and functions */
 TYPE_1__ cm_base ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

__attribute__((used)) static inline u32 am33xx_cm_read_reg(u16 inst, u16 idx)
{
	return readl_relaxed(cm_base.va + inst + idx);
}