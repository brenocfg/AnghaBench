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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  crypto4xx_memcpy_swab32 (int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static inline void crypto4xx_memcpy_to_le32(__le32 *dst, const void *buf,
					    size_t len)
{
	crypto4xx_memcpy_swab32((u32 *)dst, buf, len);
}