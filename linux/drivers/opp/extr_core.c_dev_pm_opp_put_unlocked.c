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
struct dev_pm_opp {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  _opp_kref_release_unlocked ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dev_pm_opp_put_unlocked(struct dev_pm_opp *opp)
{
	kref_put(&opp->kref, _opp_kref_release_unlocked);
}