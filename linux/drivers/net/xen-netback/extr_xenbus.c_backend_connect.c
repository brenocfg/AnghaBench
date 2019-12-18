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
struct backend_info {scalar_t__ vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  connect (struct backend_info*) ; 

__attribute__((used)) static void backend_connect(struct backend_info *be)
{
	if (be->vif)
		connect(be);
}