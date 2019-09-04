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
typedef  int uint32_t ;
struct link_encoder {int dummy; } ;
struct dce110_link_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIG_BE_EN_CNTL ; 
 int /*<<< orphan*/  DIG_ENABLE ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct dce110_link_encoder* TO_DCE110_LINK_ENC (struct link_encoder*) ; 

bool dce110_is_dig_enabled(struct link_encoder *enc)
{
	struct dce110_link_encoder *enc110 = TO_DCE110_LINK_ENC(enc);
	uint32_t value;

	REG_GET(DIG_BE_EN_CNTL, DIG_ENABLE, &value);
	return value;
}