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
typedef  scalar_t__ u8 ;
struct lm63_data {scalar_t__* temp8; scalar_t__ remote_unsigned; } ;

/* Variables and functions */
 int TEMP8_FROM_REG (scalar_t__) ; 

__attribute__((used)) static inline int temp8_from_reg(struct lm63_data *data, int nr)
{
	if (data->remote_unsigned)
		return TEMP8_FROM_REG((u8)data->temp8[nr]);
	return TEMP8_FROM_REG(data->temp8[nr]);
}