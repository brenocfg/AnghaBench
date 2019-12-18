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
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ath10k_pci_validate_cal(void *data, size_t size)
{
	__le16 *cal_words = data;
	u16 checksum = 0;
	size_t i;

	if (size % 2 != 0)
		return false;

	for (i = 0; i < size / 2; i++)
		checksum ^= le16_to_cpu(cal_words[i]);

	return checksum == 0xffff;
}