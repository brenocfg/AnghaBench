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
struct TYPE_3__ {scalar_t__* port_array; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 int SCA_MAX_PORTS ; 
 int /*<<< orphan*/  reset_port (scalar_t__) ; 

__attribute__((used)) static void reset_adapter(SLMP_INFO *info)
{
	int i;

	for ( i=0; i < SCA_MAX_PORTS; ++i) {
		if (info->port_array[i])
			reset_port(info->port_array[i]);
	}
}