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
 int PVC_VISIBLE_CHARS ; 
 int /*<<< orphan*/  pvc_write_string (unsigned char const*,int /*<<< orphan*/ ,int) ; 
 int strlen (unsigned char const*) ; 

void pvc_dump_string(const unsigned char *str)
{
	int len = strlen(str);

	pvc_write_string(str, 0, 0);
	if (len > PVC_VISIBLE_CHARS)
		pvc_write_string(&str[PVC_VISIBLE_CHARS], 0, 1);
}