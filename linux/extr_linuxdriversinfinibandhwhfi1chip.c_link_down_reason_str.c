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
typedef  size_t u8 ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 char** link_down_reason_strs ; 

__attribute__((used)) static const char *link_down_reason_str(u8 reason)
{
	const char *str = NULL;

	if (reason < ARRAY_SIZE(link_down_reason_strs))
		str = link_down_reason_strs[reason];
	if (!str)
		str = "(invalid)";

	return str;
}