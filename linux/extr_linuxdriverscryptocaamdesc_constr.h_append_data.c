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

/* Variables and functions */
 int CAAM_CMD_SZ ; 
 scalar_t__ caam32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_caam32 (scalar_t__) ; 
 int /*<<< orphan*/ * desc_end (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 

__attribute__((used)) static inline void append_data(u32 * const desc, const void *data, int len)
{
	u32 *offset = desc_end(desc);

	if (len) /* avoid sparse warning: memcpy with byte count of 0 */
		memcpy(offset, data, len);

	(*desc) = cpu_to_caam32(caam32_to_cpu(*desc) +
				(len + CAAM_CMD_SZ - 1) / CAAM_CMD_SZ);
}