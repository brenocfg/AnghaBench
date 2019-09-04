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
struct rdma_restrack_entry {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restrack_release ; 

int rdma_restrack_put(struct rdma_restrack_entry *res)
{
	return kref_put(&res->kref, restrack_release);
}