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
struct TYPE_2__ {int /*<<< orphan*/  hisax_d_if; } ;
struct fritz_adapter {TYPE_1__ isac; } ;

/* Variables and functions */
 int /*<<< orphan*/  hisax_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct fritz_adapter*) ; 

__attribute__((used)) static void delete_adapter(struct fritz_adapter *adapter)
{
	hisax_unregister(&adapter->isac.hisax_d_if);
	kfree(adapter);
}