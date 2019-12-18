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
struct link_encoder {int dummy; } ;
struct dcn10_link_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_HPD_CONTROL ; 
 int /*<<< orphan*/  DC_HPD_EN ; 
 int /*<<< orphan*/  HPD_REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn10_link_encoder* TO_DCN10_LINK_ENC (struct link_encoder*) ; 

void dcn10_link_encoder_disable_hpd(struct link_encoder *enc)
{
	struct dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);

	HPD_REG_UPDATE(DC_HPD_CONTROL,
			DC_HPD_EN, 0);
}