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
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* dummy_stm ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int nr_dummies ; 
 int /*<<< orphan*/  stm_unregister_device (TYPE_1__*) ; 

__attribute__((used)) static void dummy_stm_exit(void)
{
	int i;

	for (i = 0; i < nr_dummies; i++) {
		stm_unregister_device(&dummy_stm[i]);
		kfree(dummy_stm[i].name);
	}
}