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
struct spk_synth {int dummy; } ;
struct TYPE_2__ {scalar_t__ alive; } ;

/* Variables and functions */
 TYPE_1__ synth_soft ; 

__attribute__((used)) static int softsynth_is_alive(struct spk_synth *synth)
{
	if (synth_soft.alive)
		return 1;
	return 0;
}