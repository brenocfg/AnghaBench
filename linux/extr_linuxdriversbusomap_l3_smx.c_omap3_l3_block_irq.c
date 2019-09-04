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
typedef  int u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct omap3_l3 {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int L3_ERROR_LOG_MULTI ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  omap3_l3_code_string (int) ; 
 int /*<<< orphan*/  omap3_l3_decode_addr (int) ; 
 int omap3_l3_decode_error_code (int) ; 
 int omap3_l3_decode_initid (int) ; 
 int /*<<< orphan*/  omap3_l3_initiator_string (int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t omap3_l3_block_irq(struct omap3_l3 *l3,
					u64 error, int error_addr)
{
	u8 code = omap3_l3_decode_error_code(error);
	u8 initid = omap3_l3_decode_initid(error);
	u8 multi = error & L3_ERROR_LOG_MULTI;
	u32 address = omap3_l3_decode_addr(error_addr);

	pr_err("%s seen by %s %s at address %x\n",
			omap3_l3_code_string(code),
			omap3_l3_initiator_string(initid),
			multi ? "Multiple Errors" : "", address);
	WARN_ON(1);

	return IRQ_HANDLED;
}