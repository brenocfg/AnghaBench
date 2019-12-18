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
struct TYPE_2__ {int hpd_source; } ;
struct dcn10_link_encoder {TYPE_1__ base; } ;
typedef  enum hpd_source_id { ____Placeholder_hpd_source_id } hpd_source_id ;

/* Variables and functions */
 int /*<<< orphan*/  DIG_BE_CNTL ; 
 int /*<<< orphan*/  DIG_HPD_SELECT ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hpd_initialize(
	struct dcn10_link_encoder *enc10)
{
	/* Associate HPD with DIG_BE */
	enum hpd_source_id hpd_source = enc10->base.hpd_source;

	REG_UPDATE(DIG_BE_CNTL, DIG_HPD_SELECT, hpd_source);
}