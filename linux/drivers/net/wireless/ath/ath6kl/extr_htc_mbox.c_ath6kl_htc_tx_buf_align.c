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

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int) ; 
 int /*<<< orphan*/ * PTR_ALIGN (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ath6kl_htc_tx_buf_align(u8 **buf, unsigned long len)
{
	u8 *align_addr;

	if (!IS_ALIGNED((unsigned long) *buf, 4)) {
		align_addr = PTR_ALIGN(*buf - 4, 4);
		memmove(align_addr, *buf, len);
		*buf = align_addr;
	}
}