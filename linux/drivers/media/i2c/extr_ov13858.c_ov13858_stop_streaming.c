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
struct ov13858 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV13858_MODE_STANDBY ; 
 int /*<<< orphan*/  OV13858_REG_MODE_SELECT ; 
 int /*<<< orphan*/  OV13858_REG_VALUE_08BIT ; 
 int ov13858_write_reg (struct ov13858*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov13858_stop_streaming(struct ov13858 *ov13858)
{
	return ov13858_write_reg(ov13858, OV13858_REG_MODE_SELECT,
				 OV13858_REG_VALUE_08BIT, OV13858_MODE_STANDBY);
}