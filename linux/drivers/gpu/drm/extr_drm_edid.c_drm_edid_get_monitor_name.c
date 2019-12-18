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
struct edid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_monitor_name (struct edid*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 

void drm_edid_get_monitor_name(struct edid *edid, char *name, int bufsize)
{
	int name_length;
	char buf[13];
	
	if (bufsize <= 0)
		return;

	name_length = min(get_monitor_name(edid, buf), bufsize - 1);
	memcpy(name, buf, name_length);
	name[name_length] = '\0';
}