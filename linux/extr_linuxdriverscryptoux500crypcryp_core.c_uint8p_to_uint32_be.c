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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32p (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 uint8p_to_uint32_be(u8 *in)
{
	u32 *data = (u32 *)in;

	return cpu_to_be32p(data);
}