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
 int /*<<< orphan*/  AUX_CONTROL ; 
 int /*<<< orphan*/  AUX_DPHY_RX_CONTROL0 ; 
 int /*<<< orphan*/  AUX_HPD_SEL ; 
 int /*<<< orphan*/  AUX_LS_READ_EN ; 
 int /*<<< orphan*/  AUX_REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUX_REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUX_RX_RECEIVE_WINDOW ; 

void dcn10_aux_initialize(struct dcn10_link_encoder *enc10)
{
	enum hpd_source_id hpd_source = enc10->base.hpd_source;

	AUX_REG_UPDATE_2(AUX_CONTROL,
			AUX_HPD_SEL, hpd_source,
			AUX_LS_READ_EN, 0);

	/* 1/4 window (the maximum allowed) */
	AUX_REG_UPDATE(AUX_DPHY_RX_CONTROL0,
			AUX_RX_RECEIVE_WINDOW, 0);
}