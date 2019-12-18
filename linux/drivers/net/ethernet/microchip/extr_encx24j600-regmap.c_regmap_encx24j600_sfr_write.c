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
typedef  int /*<<< orphan*/  u8 ;
struct encx24j600_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCRCODE ; 
 int /*<<< orphan*/  WCRU ; 
 int regmap_encx24j600_sfr_update (struct encx24j600_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regmap_encx24j600_sfr_write(void *context, u8 reg, u8 *val,
				       size_t len)
{
	struct encx24j600_context *ctx = context;

	return regmap_encx24j600_sfr_update(ctx, reg, val, len, WCRU, WCRCODE);
}