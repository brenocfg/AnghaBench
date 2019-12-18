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
struct w83627ehf_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_word_sized (int) ; 
 int w83627ehf_read_value (struct w83627ehf_data*,int) ; 

__attribute__((used)) static u16 w83627ehf_read_temp(struct w83627ehf_data *data, u16 reg)
{
	u16 res;

	res = w83627ehf_read_value(data, reg);
	if (!is_word_sized(reg))
		res <<= 8;

	return res;
}