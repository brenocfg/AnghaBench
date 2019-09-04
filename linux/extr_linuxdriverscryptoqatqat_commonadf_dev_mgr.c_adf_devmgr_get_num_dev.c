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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ adf_get_num_dettached_vfs () ; 
 scalar_t__ num_devices ; 

void adf_devmgr_get_num_dev(uint32_t *num)
{
	*num = num_devices - adf_get_num_dettached_vfs();
}