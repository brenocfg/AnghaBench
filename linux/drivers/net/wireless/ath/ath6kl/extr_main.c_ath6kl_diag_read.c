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
typedef  int u32 ;
struct ath6kl {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int ath6kl_diag_read32 (struct ath6kl*,int,int*) ; 

int ath6kl_diag_read(struct ath6kl *ar, u32 address, void *data, u32 length)
{
	u32 count, *buf = data;
	int ret;

	if (WARN_ON(length % 4))
		return -EINVAL;

	for (count = 0; count < length / 4; count++, address += 4) {
		ret = ath6kl_diag_read32(ar, address, &buf[count]);
		if (ret)
			return ret;
	}

	return 0;
}