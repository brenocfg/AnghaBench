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
struct ehea_q_skb_arr {int len; scalar_t__ os_skbs; scalar_t__ index; int /*<<< orphan*/  arr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  vzalloc (int) ; 

__attribute__((used)) static int ehea_init_q_skba(struct ehea_q_skb_arr *q_skba, int max_q_entries)
{
	int arr_size = sizeof(void *) * max_q_entries;

	q_skba->arr = vzalloc(arr_size);
	if (!q_skba->arr)
		return -ENOMEM;

	q_skba->len = max_q_entries;
	q_skba->index = 0;
	q_skba->os_skbs = 0;

	return 0;
}