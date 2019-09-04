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
struct hinic_sq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_sq_skb_arr (struct hinic_sq*) ; 

void hinic_clean_sq(struct hinic_sq *sq)
{
	free_sq_skb_arr(sq);
}