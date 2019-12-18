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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  synth_buffer_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synth_start () ; 

void synth_putwc_s(u16 wc)
{
	synth_buffer_add(wc);
	synth_start();
}