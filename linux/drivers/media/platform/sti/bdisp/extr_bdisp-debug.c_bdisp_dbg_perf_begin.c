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
struct TYPE_2__ {int /*<<< orphan*/  hw_start; } ;
struct bdisp_dev {TYPE_1__ dbg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get () ; 

void bdisp_dbg_perf_begin(struct bdisp_dev *bdisp)
{
	bdisp->dbg.hw_start = ktime_get();
}