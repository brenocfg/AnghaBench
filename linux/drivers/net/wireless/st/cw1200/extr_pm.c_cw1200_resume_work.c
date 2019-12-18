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
struct delayed_work {int dummy; } ;
struct cw1200_common {int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 int queue_delayed_work (int /*<<< orphan*/ ,struct delayed_work*,unsigned long) ; 

__attribute__((used)) static int cw1200_resume_work(struct cw1200_common *priv,
			       struct delayed_work *work,
			       unsigned long tmo)
{
	if ((long)tmo < 0)
		return 1;

	return queue_delayed_work(priv->workqueue, work, tmo);
}