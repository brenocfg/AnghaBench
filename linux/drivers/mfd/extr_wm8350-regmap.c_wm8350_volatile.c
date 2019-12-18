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
struct device {int dummy; } ;
struct TYPE_2__ {int vol; } ;

/* Variables and functions */
 TYPE_1__* wm8350_reg_io_map ; 

__attribute__((used)) static bool wm8350_volatile(struct device *dev, unsigned int reg)
{
	return wm8350_reg_io_map[reg].vol;
}