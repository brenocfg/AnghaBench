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
struct s_smc {int dummy; } ;
struct s_phy {scalar_t__ np; int /*<<< orphan*/  pcm_timer0; int /*<<< orphan*/  timer0_exp; } ;

/* Variables and functions */
 scalar_t__ EVENT_PCM ; 
 int /*<<< orphan*/  EV_TOKEN (scalar_t__,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  smt_timer_start (struct s_smc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_pcm_timer0(struct s_smc *smc, u_long value, int event,
			     struct s_phy *phy)
{
	phy->timer0_exp = FALSE ;       /* clear timer event flag */
	smt_timer_start(smc,&phy->pcm_timer0,value,
		EV_TOKEN(EVENT_PCM+phy->np,event)) ;
}