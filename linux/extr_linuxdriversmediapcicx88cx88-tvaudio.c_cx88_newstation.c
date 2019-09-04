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
struct cx88_core {int /*<<< orphan*/  last_change; int /*<<< orphan*/  audiomode_manual; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNSET ; 
 int /*<<< orphan*/  jiffies ; 

void cx88_newstation(struct cx88_core *core)
{
	core->audiomode_manual = UNSET;
	core->last_change = jiffies;
}