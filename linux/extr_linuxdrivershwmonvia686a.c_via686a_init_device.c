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
struct via686a_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIA686A_REG_CONFIG ; 
 int /*<<< orphan*/  VIA686A_REG_TEMP_MODE ; 
 int VIA686A_TEMP_MODE_CONTINUOUS ; 
 int VIA686A_TEMP_MODE_MASK ; 
 int via686a_read_value (struct via686a_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  via686a_update_fan_div (struct via686a_data*) ; 
 int /*<<< orphan*/  via686a_write_value (struct via686a_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void via686a_init_device(struct via686a_data *data)
{
	u8 reg;

	/* Start monitoring */
	reg = via686a_read_value(data, VIA686A_REG_CONFIG);
	via686a_write_value(data, VIA686A_REG_CONFIG, (reg | 0x01) & 0x7F);

	/* Configure temp interrupt mode for continuous-interrupt operation */
	reg = via686a_read_value(data, VIA686A_REG_TEMP_MODE);
	via686a_write_value(data, VIA686A_REG_TEMP_MODE,
			    (reg & ~VIA686A_TEMP_MODE_MASK)
			    | VIA686A_TEMP_MODE_CONTINUOUS);

	/* Pre-read fan clock divisor values */
	via686a_update_fan_div(data);
}