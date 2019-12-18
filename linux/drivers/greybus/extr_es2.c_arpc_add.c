#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct es2_ap_dev {int /*<<< orphan*/  arpcs; int /*<<< orphan*/  arpc_id_cycle; } ;
struct arpc {int active; int /*<<< orphan*/  list; TYPE_1__* req; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void arpc_add(struct es2_ap_dev *es2, struct arpc *rpc)
{
	rpc->active = true;
	rpc->req->id = cpu_to_le16(es2->arpc_id_cycle++);
	list_add_tail(&rpc->list, &es2->arpcs);
}