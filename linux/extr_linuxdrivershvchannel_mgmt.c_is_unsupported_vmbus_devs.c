#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_le ;
struct TYPE_3__ {int /*<<< orphan*/  guid; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  uuid_le_cmp (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 TYPE_1__* vmbus_unsupported_devs ; 

__attribute__((used)) static bool is_unsupported_vmbus_devs(const uuid_le *guid)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(vmbus_unsupported_devs); i++)
		if (!uuid_le_cmp(*guid, vmbus_unsupported_devs[i].guid))
			return true;
	return false;
}