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
struct psmouse {int dummy; } ;

/* Variables and functions */
 int cypress_read_fw_version (struct psmouse*) ; 
 int cypress_read_tp_metrics (struct psmouse*) ; 

__attribute__((used)) static int cypress_query_hardware(struct psmouse *psmouse)
{
	int ret;

	ret = cypress_read_fw_version(psmouse);
	if (ret)
		return ret;

	ret = cypress_read_tp_metrics(psmouse);
	if (ret)
		return ret;

	return 0;
}