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
struct ccu_mux_internal {int dummy; } ;
struct ccu_common {int dummy; } ;

/* Variables and functions */
 unsigned long ccu_mux_get_prediv (struct ccu_common*,struct ccu_mux_internal*,int) ; 

unsigned long ccu_mux_helper_apply_prediv(struct ccu_common *common,
					  struct ccu_mux_internal *cm,
					  int parent_index,
					  unsigned long parent_rate)
{
	return parent_rate / ccu_mux_get_prediv(common, cm, parent_index);
}