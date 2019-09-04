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
struct cxl_afu {int /*<<< orphan*/  configured_state; } ;

/* Variables and functions */
 int atomic_inc_unless_negative (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool cxl_afu_configured_get(struct cxl_afu *afu)
{
	return atomic_inc_unless_negative(&afu->configured_state);
}