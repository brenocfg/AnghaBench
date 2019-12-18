#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  list; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;
struct nfp_fl_payload_link {TYPE_2__ sub_flow; TYPE_1__ merge_flow; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfp_fl_payload_link*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfp_flower_unlink_flow(struct nfp_fl_payload_link *link)
{
	list_del(&link->merge_flow.list);
	list_del(&link->sub_flow.list);
	kfree(link);
}