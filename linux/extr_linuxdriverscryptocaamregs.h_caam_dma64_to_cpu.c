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
 scalar_t__ caam32_to_cpu (int /*<<< orphan*/ ) ; 
 int caam64_to_cpu (int) ; 
 scalar_t__ caam_imx ; 
 int /*<<< orphan*/  lower_32_bits (int) ; 
 int /*<<< orphan*/  upper_32_bits (int) ; 

__attribute__((used)) static inline u64 caam_dma64_to_cpu(u64 value)
{
	if (caam_imx)
		return (((u64)caam32_to_cpu(lower_32_bits(value)) << 32) |
			 (u64)caam32_to_cpu(upper_32_bits(value)));

	return caam64_to_cpu(value);
}