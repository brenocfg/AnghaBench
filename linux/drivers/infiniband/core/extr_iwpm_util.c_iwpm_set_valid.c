#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_2__ {int* client_list; } ;

/* Variables and functions */
 TYPE_1__ iwpm_admin ; 

void iwpm_set_valid(u8 nl_client, int valid)
{
	iwpm_admin.client_list[nl_client] = valid;
}