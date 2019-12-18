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
typedef  int u16 ;
struct wcn36xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCN36XX_DXE_INT_MASK_REG ; 
 int /*<<< orphan*/  wcn36xx_dxe_read_register (struct wcn36xx*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  wcn36xx_dxe_write_register (struct wcn36xx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wcn36xx_dxe_enable_ch_int(struct wcn36xx *wcn, u16 wcn_ch)
{
	int reg_data = 0;

	wcn36xx_dxe_read_register(wcn,
				  WCN36XX_DXE_INT_MASK_REG,
				  &reg_data);

	reg_data |= wcn_ch;

	wcn36xx_dxe_write_register(wcn,
				   WCN36XX_DXE_INT_MASK_REG,
				   (int)reg_data);
	return 0;
}