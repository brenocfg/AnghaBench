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
typedef  int u8 ;

/* Variables and functions */
 int PVC_VISIBLE_CHARS ; 
 int /*<<< orphan*/  pvc_write_string (unsigned char const*,int,int) ; 
 int strlen (unsigned char const*) ; 

void pvc_write_string_centered(const unsigned char *str, int line)
{
	int len = strlen(str);
	u8 addr;

	if (len > PVC_VISIBLE_CHARS)
		addr = 0;
	else
		addr = (PVC_VISIBLE_CHARS - strlen(str))/2;

	pvc_write_string(str, addr, line);
}