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
typedef  int /*<<< orphan*/  u32 ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (unsigned long,int) ; 
 scalar_t__ KS8695_T1PD ; 
 scalar_t__ KS8695_T1TC ; 
 scalar_t__ KS8695_TMCON ; 
 scalar_t__ KS8695_TMR_VA ; 
 int /*<<< orphan*/  TMCON_T1EN ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ks8695_set_next_event(unsigned long cycles,
				 struct clock_event_device *evt)

{
	u32 half = DIV_ROUND_CLOSEST(cycles, 2);
	u32 tmcon;

	/* Disable timer 1 */
	tmcon = readl_relaxed(KS8695_TMR_VA + KS8695_TMCON);
	tmcon &= ~TMCON_T1EN;
	writel_relaxed(tmcon, KS8695_TMR_VA + KS8695_TMCON);

	/* Both registers need to count down */
	writel_relaxed(half, KS8695_TMR_VA + KS8695_T1TC);
	writel_relaxed(half, KS8695_TMR_VA + KS8695_T1PD);

	/* Re-enable timer1 */
	tmcon |= TMCON_T1EN;
	writel_relaxed(tmcon, KS8695_TMR_VA + KS8695_TMCON);

	return 0;
}