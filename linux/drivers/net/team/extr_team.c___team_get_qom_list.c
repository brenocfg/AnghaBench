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
typedef  int u16 ;
struct team {struct list_head* qom_lists; } ;
struct list_head {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct list_head *__team_get_qom_list(struct team *team, u16 queue_id)
{
	return &team->qom_lists[queue_id - 1];
}