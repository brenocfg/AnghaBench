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
struct bus_type {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ ap_configuration ; 
 scalar_t__ ap_max_domain_id ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t ap_max_domain_id_show(struct bus_type *bus, char *buf)
{
	int max_domain_id;

	if (ap_configuration)
		max_domain_id = ap_max_domain_id ? : -1;
	else
		max_domain_id = 15;
	return snprintf(buf, PAGE_SIZE, "%d\n", max_domain_id);
}