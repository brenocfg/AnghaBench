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
typedef  enum slb_index { ____Placeholder_slb_index } slb_index ;
struct TYPE_4__ {TYPE_1__* save_area; } ;
struct TYPE_3__ {int /*<<< orphan*/  esid; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 TYPE_2__* get_slb_shadow () ; 

__attribute__((used)) static inline void slb_shadow_clear(enum slb_index index)
{
	WRITE_ONCE(get_slb_shadow()->save_area[index].esid, cpu_to_be64(index));
}