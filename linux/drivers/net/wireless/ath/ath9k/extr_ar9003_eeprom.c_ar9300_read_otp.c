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
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar9300_otp_read_word (struct ath_hw*,int,int*) ; 

__attribute__((used)) static bool ar9300_read_otp(struct ath_hw *ah, int address, u8 *buffer,
			    int count)
{
	u32 data;
	int i;

	for (i = 0; i < count; i++) {
		int offset = 8 * ((address - i) % 4);
		if (!ar9300_otp_read_word(ah, (address - i) / 4, &data))
			return false;

		buffer[i] = (data >> offset) & 0xff;
	}

	return true;
}