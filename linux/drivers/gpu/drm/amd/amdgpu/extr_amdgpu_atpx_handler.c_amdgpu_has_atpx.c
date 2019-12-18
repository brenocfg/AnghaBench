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
struct TYPE_2__ {int atpx_detected; } ;

/* Variables and functions */
 TYPE_1__ amdgpu_atpx_priv ; 

bool amdgpu_has_atpx(void) {
	return amdgpu_atpx_priv.atpx_detected;
}