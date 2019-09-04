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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ caam32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ caam_little_end ; 
 int /*<<< orphan*/  cpu_to_caam32 (scalar_t__) ; 
 int /*<<< orphan*/ * desc_end (int /*<<< orphan*/ * const) ; 
 scalar_t__ lower_32_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void append_u64(u32 * const desc, u64 data)
{
	u32 *offset = desc_end(desc);

	/* Only 32-bit alignment is guaranteed in descriptor buffer */
	if (caam_little_end) {
		*offset = cpu_to_caam32(lower_32_bits(data));
		*(++offset) = cpu_to_caam32(upper_32_bits(data));
	} else {
		*offset = cpu_to_caam32(upper_32_bits(data));
		*(++offset) = cpu_to_caam32(lower_32_bits(data));
	}

	(*desc) = cpu_to_caam32(caam32_to_cpu(*desc) + 2);
}