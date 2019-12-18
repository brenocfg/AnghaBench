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
typedef  size_t ssize_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  resource_alignment_lock ; 
 char* resource_alignment_param ; 
 size_t snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t resource_alignment_show(struct bus_type *bus, char *buf)
{
	size_t count = 0;

	spin_lock(&resource_alignment_lock);
	if (resource_alignment_param)
		count = snprintf(buf, PAGE_SIZE, "%s", resource_alignment_param);
	spin_unlock(&resource_alignment_lock);

	/*
	 * When set by the command line, resource_alignment_param will not
	 * have a trailing line feed, which is ugly. So conditionally add
	 * it here.
	 */
	if (count >= 2 && buf[count - 2] != '\n' && count < PAGE_SIZE - 1) {
		buf[count - 1] = '\n';
		buf[count++] = 0;
	}

	return count;
}