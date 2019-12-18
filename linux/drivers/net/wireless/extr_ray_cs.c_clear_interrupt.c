#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ amem; } ;
typedef  TYPE_1__ ray_dev_t ;

/* Variables and functions */
 scalar_t__ CIS_OFFSET ; 
 scalar_t__ HCS_INTR_OFFSET ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void clear_interrupt(ray_dev_t *local)
{
	writeb(0, local->amem + CIS_OFFSET + HCS_INTR_OFFSET);
}