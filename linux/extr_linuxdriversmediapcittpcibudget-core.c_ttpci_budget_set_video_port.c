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
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct budget {int video_port; int /*<<< orphan*/  feedlock; scalar_t__ feeding; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_ts_capture (struct budget*) ; 
 int /*<<< orphan*/  stop_ts_capture (struct budget*) ; 

void ttpci_budget_set_video_port(struct saa7146_dev *dev, int video_port)
{
	struct budget *budget = (struct budget *) dev->ext_priv;

	spin_lock(&budget->feedlock);
	budget->video_port = video_port;
	if (budget->feeding) {
		stop_ts_capture(budget);
		start_ts_capture(budget);
	}
	spin_unlock(&budget->feedlock);
}