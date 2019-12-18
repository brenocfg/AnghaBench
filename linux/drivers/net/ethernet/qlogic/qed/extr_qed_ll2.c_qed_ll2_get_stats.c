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
typedef  int /*<<< orphan*/  u8 ;
struct qed_ll2_stats {int dummy; } ;

/* Variables and functions */
 int __qed_ll2_get_stats (void*,int /*<<< orphan*/ ,struct qed_ll2_stats*) ; 
 int /*<<< orphan*/  memset (struct qed_ll2_stats*,int /*<<< orphan*/ ,int) ; 

int qed_ll2_get_stats(void *cxt,
		      u8 connection_handle, struct qed_ll2_stats *p_stats)
{
	memset(p_stats, 0, sizeof(*p_stats));
	return __qed_ll2_get_stats(cxt, connection_handle, p_stats);
}