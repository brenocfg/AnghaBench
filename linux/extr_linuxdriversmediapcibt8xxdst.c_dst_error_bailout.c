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
struct dst_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  dst_pio_disable (struct dst_state*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rdc_8820_reset (struct dst_state*) ; 

int dst_error_bailout(struct dst_state *state)
{
	dprintk(2, "Trying to bailout from previous error.\n");
	rdc_8820_reset(state);
	dst_pio_disable(state);
	msleep(10);

	return 0;
}