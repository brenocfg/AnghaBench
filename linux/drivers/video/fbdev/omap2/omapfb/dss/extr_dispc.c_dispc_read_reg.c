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
struct TYPE_2__ {scalar_t__ const base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_readl (scalar_t__ const) ; 
 TYPE_1__ dispc ; 

__attribute__((used)) static inline u32 dispc_read_reg(const u16 idx)
{
	return __raw_readl(dispc.base + idx);
}