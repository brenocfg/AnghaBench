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
struct spk_synth {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ module_status ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spk_mutex ; 
 struct spk_synth* synth ; 
 int /*<<< orphan*/  synth_release () ; 

void synth_remove(struct spk_synth *in_synth)
{
	mutex_lock(&spk_mutex);
	if (synth == in_synth)
		synth_release();
	list_del(&in_synth->node);
	module_status = 0;
	mutex_unlock(&spk_mutex);
}