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
struct es2_ap_dev {int dummy; } ;
struct arpc {int active; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void arpc_del(struct es2_ap_dev *es2, struct arpc *rpc)
{
	if (rpc->active) {
		rpc->active = false;
		list_del(&rpc->list);
	}
}