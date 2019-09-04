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
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* dfl_devs ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dfl_ids_destroy(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(dfl_devs); i++)
		idr_destroy(&dfl_devs[i].id);
}