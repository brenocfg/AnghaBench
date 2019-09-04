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
struct ib_mad_mgmt_method_table {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct ib_mad_mgmt_method_table* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int allocate_method_table(struct ib_mad_mgmt_method_table **method)
{
	/* Allocate management method table */
	*method = kzalloc(sizeof **method, GFP_ATOMIC);
	return (*method) ? 0 : (-ENOMEM);
}