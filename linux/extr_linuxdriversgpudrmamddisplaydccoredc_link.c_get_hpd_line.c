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
struct gpio {int dummy; } ;
struct dc_link {TYPE_1__* ctx; int /*<<< orphan*/  link_id; } ;
typedef  enum hpd_source_id { ____Placeholder_hpd_source_id } hpd_source_id ;
struct TYPE_2__ {int /*<<< orphan*/  gpio_service; int /*<<< orphan*/  dc_bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
#define  DC_IRQ_SOURCE_HPD1 133 
#define  DC_IRQ_SOURCE_HPD2 132 
#define  DC_IRQ_SOURCE_HPD3 131 
#define  DC_IRQ_SOURCE_HPD4 130 
#define  DC_IRQ_SOURCE_HPD5 129 
#define  DC_IRQ_SOURCE_HPD6 128 
 int HPD_SOURCEID1 ; 
 int HPD_SOURCEID2 ; 
 int HPD_SOURCEID3 ; 
 int HPD_SOURCEID4 ; 
 int HPD_SOURCEID5 ; 
 int HPD_SOURCEID6 ; 
 int HPD_SOURCEID_UNKNOWN ; 
 int /*<<< orphan*/  dal_gpio_destroy_irq (struct gpio**) ; 
 int dal_irq_get_source (struct gpio*) ; 
 struct gpio* get_hpd_gpio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum hpd_source_id get_hpd_line(
		struct dc_link *link)
{
	struct gpio *hpd;
	enum hpd_source_id hpd_id = HPD_SOURCEID_UNKNOWN;

	hpd = get_hpd_gpio(link->ctx->dc_bios, link->link_id, link->ctx->gpio_service);

	if (hpd) {
		switch (dal_irq_get_source(hpd)) {
		case DC_IRQ_SOURCE_HPD1:
			hpd_id = HPD_SOURCEID1;
		break;
		case DC_IRQ_SOURCE_HPD2:
			hpd_id = HPD_SOURCEID2;
		break;
		case DC_IRQ_SOURCE_HPD3:
			hpd_id = HPD_SOURCEID3;
		break;
		case DC_IRQ_SOURCE_HPD4:
			hpd_id = HPD_SOURCEID4;
		break;
		case DC_IRQ_SOURCE_HPD5:
			hpd_id = HPD_SOURCEID5;
		break;
		case DC_IRQ_SOURCE_HPD6:
			hpd_id = HPD_SOURCEID6;
		break;
		default:
			BREAK_TO_DEBUGGER();
		break;
		}

		dal_gpio_destroy_irq(&hpd);
	}

	return hpd_id;
}