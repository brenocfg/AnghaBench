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
struct dr_hw_ste_format {int* tag; scalar_t__* mask; } ;

/* Variables and functions */

__attribute__((used)) static void dr_ste_set_always_miss(struct dr_hw_ste_format *hw_ste)
{
	hw_ste->tag[0] = 0xdc;
	hw_ste->mask[0] = 0;
}