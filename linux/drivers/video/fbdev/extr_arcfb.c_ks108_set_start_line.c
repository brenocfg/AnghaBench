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
struct arcfb_par {int dummy; } ;

/* Variables and functions */
 unsigned char KS_SET_DPY_START_LINE ; 
 int /*<<< orphan*/  ks108_writeb_ctl (struct arcfb_par*,unsigned int,unsigned char) ; 

__attribute__((used)) static void ks108_set_start_line(struct arcfb_par *par,
				unsigned int chipindex, unsigned char y)
{
	ks108_writeb_ctl(par, chipindex, KS_SET_DPY_START_LINE|y);
}