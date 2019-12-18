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
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_MASTER_UPDATE_LOCK ; 
 int /*<<< orphan*/  OTG_MASTER_UPDATE_LOCK_VUPDATE_KEEPOUT_EN ; 
 int /*<<< orphan*/  OTG_VUPDATE_KEEPOUT ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void optc2_triplebuffer_unlock(struct timing_generator *optc)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET(OTG_MASTER_UPDATE_LOCK, 0,
		OTG_MASTER_UPDATE_LOCK, 0);

	REG_SET(OTG_VUPDATE_KEEPOUT, 0,
		OTG_MASTER_UPDATE_LOCK_VUPDATE_KEEPOUT_EN, 0);

}