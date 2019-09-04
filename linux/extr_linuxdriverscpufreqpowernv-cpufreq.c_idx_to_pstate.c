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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  driver_data; } ;
struct TYPE_3__ {unsigned int nr_pstates; size_t nominal; } ;

/* Variables and functions */
 TYPE_2__* powernv_freqs ; 
 TYPE_1__ powernv_pstate_info ; 
 int /*<<< orphan*/  pr_warn_once (char*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline u8 idx_to_pstate(unsigned int i)
{
	if (unlikely(i >= powernv_pstate_info.nr_pstates)) {
		pr_warn_once("idx_to_pstate: index %u is out of bound\n", i);
		return powernv_freqs[powernv_pstate_info.nominal].driver_data;
	}

	return powernv_freqs[i].driver_data;
}