#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int delay_linear; } ;
struct TYPE_4__ {TYPE_1__ membw; } ;

/* Variables and functions */
 size_t RDT_RESOURCE_MBA ; 
 TYPE_2__* rdt_resources_all ; 

__attribute__((used)) static inline bool is_mba_linear(void)
{
	return rdt_resources_all[RDT_RESOURCE_MBA].membw.delay_linear;
}