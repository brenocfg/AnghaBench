#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_3__ {int size; int /*<<< orphan*/  timer; scalar_t__ map; } ;
struct mthca_dev {TYPE_1__ catas_err; } ;
struct TYPE_4__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 scalar_t__ MTHCA_CATAS_POLL_INTERVAL ; 
 TYPE_2__ catas_err ; 
 struct mthca_dev* dev ; 
 struct mthca_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_catas (struct mthca_dev*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 

__attribute__((used)) static void poll_catas(struct timer_list *t)
{
	struct mthca_dev *dev = from_timer(dev, t, catas_err.timer);
	int i;

	for (i = 0; i < dev->catas_err.size; ++i)
		if (readl(dev->catas_err.map + i)) {
			handle_catas(dev);
			return;
		}

	mod_timer(&dev->catas_err.timer,
		  round_jiffies(jiffies + MTHCA_CATAS_POLL_INTERVAL));
}