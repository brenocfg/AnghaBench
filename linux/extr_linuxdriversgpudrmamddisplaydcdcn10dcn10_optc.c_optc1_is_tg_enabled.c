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
typedef  scalar_t__ uint32_t ;
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_CONTROL ; 
 int /*<<< orphan*/  OTG_MASTER_EN ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

bool optc1_is_tg_enabled(struct timing_generator *optc)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);
	uint32_t otg_enabled = 0;

	REG_GET(OTG_CONTROL, OTG_MASTER_EN, &otg_enabled);

	return (otg_enabled != 0);

}