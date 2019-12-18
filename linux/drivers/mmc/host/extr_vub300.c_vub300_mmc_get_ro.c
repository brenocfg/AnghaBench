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
struct vub300_mmc_host {int read_only; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 struct vub300_mmc_host* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static int vub300_mmc_get_ro(struct mmc_host *mmc)
{
	struct vub300_mmc_host *vub300 = mmc_priv(mmc);
	return vub300->read_only;
}