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
struct TYPE_3__ {struct TYPE_3__* keycode; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 TYPE_1__** adbhid ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void adbhid_input_unregister(int id)
{
	input_unregister_device(adbhid[id]->input);
	kfree(adbhid[id]->keycode);
	kfree(adbhid[id]);
	adbhid[id] = NULL;
}