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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t show_tabletExecute(struct device *dev, struct device_attribute *attr, char *buf)
{
	/* There is nothing useful to display, so a one-line manual
	 * is in order...
	 */
	return snprintf(buf, PAGE_SIZE,
			"Write anything to this file to program your tablet.\n");
}