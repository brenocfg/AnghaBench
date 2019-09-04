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
struct lm90_data {int flags; } ;

/* Variables and functions */
 int LM90_FLAG_ADT7461_EXT ; 

__attribute__((used)) static u16 temp_to_u16_adt7461(struct lm90_data *data, long val)
{
	if (data->flags & LM90_FLAG_ADT7461_EXT) {
		if (val <= -64000)
			return 0;
		if (val >= 191750)
			return 0xFFC0;
		return (val + 64000 + 125) / 250 * 64;
	}
	if (val <= 0)
		return 0;
	if (val >= 127750)
		return 0x7FC0;
	return (val + 125) / 250 * 64;
}