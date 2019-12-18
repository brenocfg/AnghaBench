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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * ap_configuration ; 
 int /*<<< orphan*/  ap_configuration_available () ; 
 scalar_t__ ap_query_configuration (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ap_init_configuration(void)
{
	if (!ap_configuration_available())
		return;

	ap_configuration = kzalloc(sizeof(*ap_configuration), GFP_KERNEL);
	if (!ap_configuration)
		return;
	if (ap_query_configuration(ap_configuration) != 0) {
		kfree(ap_configuration);
		ap_configuration = NULL;
		return;
	}
}