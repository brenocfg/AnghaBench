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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  drm_mga_private_t ;

/* Variables and functions */
 scalar_t__ MGA_ENDPRDMASTS ; 
 scalar_t__ MGA_ENGINE_IDLE_MASK ; 
 scalar_t__ MGA_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGA_STATUS ; 

__attribute__((used)) static __inline__ int mga_is_idle(drm_mga_private_t *dev_priv)
{
	u32 status = MGA_READ(MGA_STATUS) & MGA_ENGINE_IDLE_MASK;
	return (status == MGA_ENDPRDMASTS);
}