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
struct abituguru3_data {int dummy; } ;

/* Variables and functions */
 int abituguru3_read (struct abituguru3_data*,int,int,int,int*) ; 

__attribute__((used)) static int abituguru3_read_increment_offset(struct abituguru3_data *data,
					    u8 bank, u8 offset, u8 count,
					    u8 *buf, int offset_count)
{
	int i, x;

	for (i = 0; i < offset_count; i++) {
		x = abituguru3_read(data, bank, offset + i, count,
				    buf + i * count);
		if (x != count) {
			if (x < 0)
				return x;
			return i * count + x;
		}
	}

	return i * count;
}