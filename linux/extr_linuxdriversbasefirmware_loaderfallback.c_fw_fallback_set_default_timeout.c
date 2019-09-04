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
struct TYPE_2__ {int /*<<< orphan*/  old_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fw_fallback_set_timeout (int /*<<< orphan*/ ) ; 
 TYPE_1__ fw_fallback_config ; 

void fw_fallback_set_default_timeout(void)
{
	__fw_fallback_set_timeout(fw_fallback_config.old_timeout);
}