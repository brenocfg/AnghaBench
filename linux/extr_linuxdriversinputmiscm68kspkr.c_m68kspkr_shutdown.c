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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_SND ; 
 int /*<<< orphan*/  SND_BELL ; 
 int /*<<< orphan*/  m68kspkr_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m68kspkr_shutdown(struct platform_device *dev)
{
	/* turn off the speaker */
	m68kspkr_event(NULL, EV_SND, SND_BELL, 0);
}