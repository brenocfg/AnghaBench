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
struct vc_map {int dummy; } ;
struct rate_estimator {int maxcps; int cps; int avcps; int interval; int ewma_log; int /*<<< orphan*/  timer; struct vc_map* vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  idt77252_est_timer ; 
 scalar_t__ jiffies ; 
 struct rate_estimator* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rate_estimator *
idt77252_init_est(struct vc_map *vc, int pcr)
{
	struct rate_estimator *est;

	est = kzalloc(sizeof(struct rate_estimator), GFP_KERNEL);
	if (!est)
		return NULL;
	est->maxcps = pcr < 0 ? -pcr : pcr;
	est->cps = est->maxcps;
	est->avcps = est->cps << 5;
	est->vc = vc;

	est->interval = 2;		/* XXX: make this configurable */
	est->ewma_log = 2;		/* XXX: make this configurable */
	timer_setup(&est->timer, idt77252_est_timer, 0);
	mod_timer(&est->timer, jiffies + ((HZ / 4) << est->interval));

	return est;
}