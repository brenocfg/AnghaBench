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
struct ci_hdrc {int /*<<< orphan*/ * ulpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ulpi_unregister_interface (int /*<<< orphan*/ *) ; 

void ci_ulpi_exit(struct ci_hdrc *ci)
{
	if (ci->ulpi) {
		ulpi_unregister_interface(ci->ulpi);
		ci->ulpi = NULL;
	}
}