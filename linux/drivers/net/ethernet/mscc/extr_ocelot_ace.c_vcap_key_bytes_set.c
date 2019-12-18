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
typedef  int u32 ;
struct vcap_data {int dummy; } ;

/* Variables and functions */
 int ENTRY_WIDTH ; 
 int /*<<< orphan*/  vcap_key_set (struct vcap_data*,int,int,int,int) ; 

__attribute__((used)) static void vcap_key_bytes_set(struct vcap_data *data, u32 offset, u8 *val,
			       u8 *msk, u32 count)
{
	u32 i, j, n = 0, value = 0, mask = 0;

	/* Data wider than 32 bits are split up in chunks of maximum 32 bits.
	 * The 32 LSB of the data are written to the 32 MSB of the TCAM.
	 */
	offset += (count * 8);
	for (i = 0; i < count; i++) {
		j = (count - i - 1);
		value += (val[j] << n);
		mask += (msk[j] << n);
		n += 8;
		if (n == ENTRY_WIDTH || (i + 1) == count) {
			offset -= n;
			vcap_key_set(data, offset, n, value, mask);
			n = 0;
			value = 0;
			mask = 0;
		}
	}
}