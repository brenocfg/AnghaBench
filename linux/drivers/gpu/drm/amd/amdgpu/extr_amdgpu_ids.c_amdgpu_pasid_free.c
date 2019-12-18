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
 int /*<<< orphan*/  amdgpu_pasid_ida ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  trace_amdgpu_pasid_freed (unsigned int) ; 

void amdgpu_pasid_free(unsigned int pasid)
{
	trace_amdgpu_pasid_freed(pasid);
	ida_simple_remove(&amdgpu_pasid_ida, pasid);
}