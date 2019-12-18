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
 scalar_t__ pvr2_context_cleanup_flag ; 
 int /*<<< orphan*/ * pvr2_context_exist_first ; 

__attribute__((used)) static int pvr2_context_shutok(void)
{
	return pvr2_context_cleanup_flag && (pvr2_context_exist_first == NULL);
}