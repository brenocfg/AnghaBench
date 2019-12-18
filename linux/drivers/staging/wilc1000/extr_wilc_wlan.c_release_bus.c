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
struct wilc {int /*<<< orphan*/  hif_cs; } ;
typedef  enum bus_release { ____Placeholder_bus_release } bus_release ;

/* Variables and functions */
 int WILC_BUS_RELEASE_ALLOW_SLEEP ; 
 int /*<<< orphan*/  chip_allow_sleep (struct wilc*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void release_bus(struct wilc *wilc, enum bus_release release)
{
	if (release == WILC_BUS_RELEASE_ALLOW_SLEEP)
		chip_allow_sleep(wilc);
	mutex_unlock(&wilc->hif_cs);
}