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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static inline u64 ZIP_QUEX_ERR_ENA_W1C(u64 param1)
{
	if (param1 <= 7)
		return 0x3600ull + (param1 & 7) * 0x8ull;
	pr_err("ZIP_QUEX_ERR_ENA_W1C: %llu\n", param1);
	return 0;
}