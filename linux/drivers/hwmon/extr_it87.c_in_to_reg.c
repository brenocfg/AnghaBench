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
struct it87_data {int dummy; } ;

/* Variables and functions */
 long DIV_ROUND_CLOSEST (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adc_lsb (struct it87_data const*,int) ; 
 int /*<<< orphan*/  clamp_val (long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 in_to_reg(const struct it87_data *data, int nr, long val)
{
	val = DIV_ROUND_CLOSEST(val * 10, adc_lsb(data, nr));
	return clamp_val(val, 0, 255);
}