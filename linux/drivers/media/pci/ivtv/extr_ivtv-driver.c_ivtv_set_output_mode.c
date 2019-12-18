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
struct ivtv {int output_mode; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ivtv_set_output_mode(struct ivtv *itv, int mode)
{
    int old_mode;

    spin_lock(&itv->lock);
    old_mode = itv->output_mode;
    if (old_mode == 0)
	itv->output_mode = old_mode = mode;
    spin_unlock(&itv->lock);
    return old_mode;
}