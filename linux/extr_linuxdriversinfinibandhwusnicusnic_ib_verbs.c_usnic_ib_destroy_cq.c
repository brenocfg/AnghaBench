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
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ib_cq*) ; 
 int /*<<< orphan*/  usnic_dbg (char*) ; 

int usnic_ib_destroy_cq(struct ib_cq *cq)
{
	usnic_dbg("\n");
	kfree(cq);
	return 0;
}