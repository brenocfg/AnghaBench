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
struct gth_device {int dummy; } ;
struct TYPE_2__ {unsigned int (* get ) (struct gth_device*,int) ;unsigned int mask; } ;

/* Variables and functions */
 unsigned int __ffs (unsigned int) ; 
 TYPE_1__* output_parms ; 
 unsigned int stub1 (struct gth_device*,int) ; 

__attribute__((used)) static unsigned int
gth_output_parm_get(struct gth_device *gth, int port, unsigned int parm)
{
	unsigned int config = output_parms[parm].get(gth, port);
	unsigned int mask = output_parms[parm].mask;
	unsigned int shift = __ffs(mask);

	config &= mask;
	config >>= shift;
	return config;
}