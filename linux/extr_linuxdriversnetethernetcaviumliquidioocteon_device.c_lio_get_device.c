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
typedef  size_t u32 ;
struct octeon_device {int dummy; } ;

/* Variables and functions */
 size_t MAX_OCTEON_DEVICES ; 
 struct octeon_device** octeon_device ; 

struct octeon_device *lio_get_device(u32 octeon_id)
{
	if (octeon_id >= MAX_OCTEON_DEVICES)
		return NULL;
	else
		return octeon_device[octeon_id];
}