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

/* Variables and functions */
 void* buff_in ; 
 void* buff_out ; 
 void* synth_buffer ; 

void synth_buffer_clear(void)
{
	buff_in = synth_buffer;
	buff_out = synth_buffer;
}