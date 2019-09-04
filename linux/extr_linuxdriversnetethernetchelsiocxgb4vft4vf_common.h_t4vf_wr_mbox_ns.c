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
struct adapter {int dummy; } ;

/* Variables and functions */
 int t4vf_wr_mbox_core (struct adapter*,void const*,int,void*,int) ; 

__attribute__((used)) static inline int t4vf_wr_mbox_ns(struct adapter *adapter, const void *cmd,
				  int size, void *rpl)
{
	return t4vf_wr_mbox_core(adapter, cmd, size, rpl, false);
}