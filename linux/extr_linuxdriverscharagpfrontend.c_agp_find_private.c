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
struct agp_file_private {scalar_t__ my_pid; struct agp_file_private* next; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_2__ {struct agp_file_private* file_priv_list; } ;

/* Variables and functions */
 TYPE_1__ agp_fe ; 

struct agp_file_private *agp_find_private(pid_t pid)
{
	struct agp_file_private *curr;

	curr = agp_fe.file_priv_list;

	while (curr != NULL) {
		if (curr->my_pid == pid)
			return curr;
		curr = curr->next;
	}

	return NULL;
}