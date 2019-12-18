#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
struct smt_timer {scalar_t__ tm_delta; int /*<<< orphan*/  tm_token; struct smt_timer* tm_next; int /*<<< orphan*/  tm_active; } ;
struct TYPE_2__ {struct smt_timer* st_queue; } ;
struct s_smc {TYPE_1__ t; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ hwt_read (struct s_smc*) ; 
 int /*<<< orphan*/  hwt_start (struct s_smc*,scalar_t__) ; 
 int /*<<< orphan*/  timer_event (struct s_smc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timer_done(struct s_smc *smc, int restart)
{
	u_long			delta ;
	struct smt_timer	*tm ;
	struct smt_timer	*next ;
	struct smt_timer	**last ;
	int			done = 0 ;

	delta = hwt_read(smc) ;
	last = &smc->t.st_queue ;
	tm = smc->t.st_queue ;
	while (tm && !done) {
		if (delta >= tm->tm_delta) {
			tm->tm_active = FALSE ;
			delta -= tm->tm_delta ;
			last = &tm->tm_next ;
			tm = tm->tm_next ;
		}
		else {
			tm->tm_delta -= delta ;
			delta = 0 ;
			done = 1 ;
		}
	}
	*last = NULL;
	next = smc->t.st_queue ;
	smc->t.st_queue = tm ;

	for ( tm = next ; tm ; tm = next) {
		next = tm->tm_next ;
		timer_event(smc,tm->tm_token) ;
	}

	if (restart && smc->t.st_queue)
		hwt_start(smc,smc->t.st_queue->tm_delta) ;
}