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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_ioread32 (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_multi_ioread32(void *hw_priv, u32 *addr,
                                u32 *val, u16 count)
{
	int i;

	for (i = 0; i < count; i++)
		val[i] = ath9k_ioread32(hw_priv, addr[i]);
}