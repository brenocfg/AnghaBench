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
typedef  int /*<<< orphan*/  u_long ;
struct timer_list {int dummy; } ;
struct ahd_softc {int hs_mailbox; scalar_t__ cmdcmplt_total; scalar_t__ int_coalescing_threshold; scalar_t__ int_coalescing_stop_threshold; int cmdcmplt_bucket; scalar_t__* cmdcmplt_counts; int /*<<< orphan*/  stat_timer; } ;

/* Variables and functions */
 int AHD_SHOW_INT_COALESCING ; 
 int AHD_STAT_BUCKETS ; 
 int /*<<< orphan*/  AHD_STAT_UPDATE_US ; 
 int ENINT_COALESCE ; 
 struct ahd_softc* ahd ; 
 int ahd_debug ; 
 int /*<<< orphan*/  ahd_enable_coalescing (struct ahd_softc*,int) ; 
 int /*<<< orphan*/  ahd_lock (struct ahd_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_timer_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_unlock (struct ahd_softc*,int /*<<< orphan*/ *) ; 
 struct ahd_softc* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  stat_timer ; 

__attribute__((used)) static void
ahd_stat_timer(struct timer_list *t)
{
	struct	ahd_softc *ahd = from_timer(ahd, t, stat_timer);
	u_long	s;
	int	enint_coal;
	
	ahd_lock(ahd, &s);

	enint_coal = ahd->hs_mailbox & ENINT_COALESCE;
	if (ahd->cmdcmplt_total > ahd->int_coalescing_threshold)
		enint_coal |= ENINT_COALESCE;
	else if (ahd->cmdcmplt_total < ahd->int_coalescing_stop_threshold)
		enint_coal &= ~ENINT_COALESCE;

	if (enint_coal != (ahd->hs_mailbox & ENINT_COALESCE)) {
		ahd_enable_coalescing(ahd, enint_coal);
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_INT_COALESCING) != 0)
			printk("%s: Interrupt coalescing "
			       "now %sabled. Cmds %d\n",
			       ahd_name(ahd),
			       (enint_coal & ENINT_COALESCE) ? "en" : "dis",
			       ahd->cmdcmplt_total);
#endif
	}

	ahd->cmdcmplt_bucket = (ahd->cmdcmplt_bucket+1) & (AHD_STAT_BUCKETS-1);
	ahd->cmdcmplt_total -= ahd->cmdcmplt_counts[ahd->cmdcmplt_bucket];
	ahd->cmdcmplt_counts[ahd->cmdcmplt_bucket] = 0;
	ahd_timer_reset(&ahd->stat_timer, AHD_STAT_UPDATE_US);
	ahd_unlock(ahd, &s);
}