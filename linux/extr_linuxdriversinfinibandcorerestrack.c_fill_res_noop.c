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
struct sk_buff {int dummy; } ;
struct rdma_restrack_entry {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int fill_res_noop(struct sk_buff *msg,
			 struct rdma_restrack_entry *entry)
{
	return 0;
}