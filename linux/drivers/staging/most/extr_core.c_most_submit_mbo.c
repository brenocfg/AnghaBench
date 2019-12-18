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
struct mbo {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 scalar_t__ WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  nq_hdm_mbo (struct mbo*) ; 

void most_submit_mbo(struct mbo *mbo)
{
	if (WARN_ONCE(!mbo || !mbo->context,
		      "bad mbo or missing channel reference\n"))
		return;

	nq_hdm_mbo(mbo);
}