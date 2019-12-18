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
typedef  int /*<<< orphan*/  value ;
typedef  scalar_t__ ulong ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
qla27xx_insert32(uint32_t value, void *buf, ulong *len)
{
	if (buf) {
		buf += *len;
		*(__le32 *)buf = cpu_to_le32(value);
	}
	*len += sizeof(value);
}