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
 int SD_RSP_TYPE_R0 ; 
 int SD_RSP_TYPE_R2 ; 

__attribute__((used)) static int sd_status_index(int resp_type)
{
	if (resp_type == SD_RSP_TYPE_R0)
		return 0;
	else if (resp_type == SD_RSP_TYPE_R2)
		return 16;

	return 5;
}