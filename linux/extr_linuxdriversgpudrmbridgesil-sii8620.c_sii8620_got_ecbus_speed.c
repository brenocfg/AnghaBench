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
struct sii8620 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURR_ECBUS_MODE ; 
 int /*<<< orphan*/  MHL_RAP_CBUS_MODE_UP ; 
 int MHL_XDS_ECBUS_S ; 
 int /*<<< orphan*/  MHL_XDS_REG (int /*<<< orphan*/ ) ; 
 int MHL_XDS_SLOT_MODE_8BIT ; 
 int /*<<< orphan*/  sii8620_ecbus_up ; 
 int /*<<< orphan*/  sii8620_mt_rap (struct sii8620*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_mt_set_cont (struct sii8620*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_mt_write_stat (struct sii8620*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sii8620_got_ecbus_speed(struct sii8620 *ctx, int ret)
{
	if (ret < 0)
		return;

	sii8620_mt_write_stat(ctx, MHL_XDS_REG(CURR_ECBUS_MODE),
			      MHL_XDS_ECBUS_S | MHL_XDS_SLOT_MODE_8BIT);
	sii8620_mt_rap(ctx, MHL_RAP_CBUS_MODE_UP);
	sii8620_mt_set_cont(ctx, sii8620_ecbus_up);
}