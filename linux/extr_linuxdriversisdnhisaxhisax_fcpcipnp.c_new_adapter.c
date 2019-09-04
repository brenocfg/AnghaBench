#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  l2l1; TYPE_3__* priv; } ;
struct hisax_b_if {TYPE_2__ ifc; } ;
struct TYPE_6__ {int /*<<< orphan*/  l2l1; TYPE_4__* priv; } ;
struct TYPE_10__ {TYPE_1__ ifc; int /*<<< orphan*/  owner; } ;
struct TYPE_9__ {TYPE_5__ hisax_d_if; } ;
struct fritz_adapter {TYPE_4__ isac; TYPE_3__* bcs; } ;
struct TYPE_8__ {int channel; struct hisax_b_if b_if; struct fritz_adapter* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  fritz_b_l2l1 ; 
 scalar_t__ hisax_register (TYPE_5__*,struct hisax_b_if**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isac_d_l2l1 ; 
 int /*<<< orphan*/  kfree (struct fritz_adapter*) ; 
 struct fritz_adapter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  protocol ; 

__attribute__((used)) static struct fritz_adapter *new_adapter(void)
{
	struct fritz_adapter *adapter;
	struct hisax_b_if *b_if[2];
	int i;

	adapter = kzalloc(sizeof(struct fritz_adapter), GFP_KERNEL);
	if (!adapter)
		return NULL;

	adapter->isac.hisax_d_if.owner = THIS_MODULE;
	adapter->isac.hisax_d_if.ifc.priv = &adapter->isac;
	adapter->isac.hisax_d_if.ifc.l2l1 = isac_d_l2l1;

	for (i = 0; i < 2; i++) {
		adapter->bcs[i].adapter = adapter;
		adapter->bcs[i].channel = i;
		adapter->bcs[i].b_if.ifc.priv = &adapter->bcs[i];
		adapter->bcs[i].b_if.ifc.l2l1 = fritz_b_l2l1;
	}

	for (i = 0; i < 2; i++)
		b_if[i] = &adapter->bcs[i].b_if;

	if (hisax_register(&adapter->isac.hisax_d_if, b_if, "fcpcipnp",
			   protocol) != 0) {
		kfree(adapter);
		adapter = NULL;
	}

	return adapter;
}