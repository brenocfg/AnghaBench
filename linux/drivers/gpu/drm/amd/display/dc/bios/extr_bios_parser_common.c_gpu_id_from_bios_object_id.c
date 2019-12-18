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
typedef  int uint32_t ;

/* Variables and functions */
 int OBJECT_ID_MASK ; 
 int OBJECT_ID_SHIFT ; 

__attribute__((used)) static uint32_t gpu_id_from_bios_object_id(uint32_t bios_object_id)
{
	return (bios_object_id & OBJECT_ID_MASK) >> OBJECT_ID_SHIFT;
}