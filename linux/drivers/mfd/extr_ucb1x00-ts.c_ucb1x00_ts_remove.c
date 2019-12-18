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
struct ucb1x00_ts {int /*<<< orphan*/  idev; } ;
struct ucb1x00_dev {struct ucb1x00_ts* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ucb1x00_ts*) ; 

__attribute__((used)) static void ucb1x00_ts_remove(struct ucb1x00_dev *dev)
{
	struct ucb1x00_ts *ts = dev->priv;

	input_unregister_device(ts->idev);
	kfree(ts);
}