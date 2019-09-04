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
struct agp_file_private {struct agp_file_private* next; struct agp_file_private* prev; } ;
struct TYPE_2__ {struct agp_file_private* file_priv_list; } ;

/* Variables and functions */
 TYPE_1__ agp_fe ; 

__attribute__((used)) static void agp_insert_file_private(struct agp_file_private * priv)
{
	struct agp_file_private *prev;

	prev = agp_fe.file_priv_list;

	if (prev != NULL)
		prev->prev = priv;
	priv->next = prev;
	agp_fe.file_priv_list = priv;
}