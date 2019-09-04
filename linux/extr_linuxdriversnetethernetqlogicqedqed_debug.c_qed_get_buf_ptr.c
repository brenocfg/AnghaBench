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
typedef  int u32 ;

/* Variables and functions */
 char* s_temp_buf ; 

__attribute__((used)) static char *qed_get_buf_ptr(void *buf, u32 offset)
{
	return buf ? (char *)buf + offset : s_temp_buf;
}