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
struct ahc_softc {TYPE_1__* platform_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  spin_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void
ahc_unlock(struct ahc_softc *ahc, unsigned long *flags)
{
	spin_unlock_irqrestore(&ahc->platform_data->spin_lock, *flags);
}