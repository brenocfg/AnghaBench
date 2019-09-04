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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void be16_to_cpu_n(const u8 *_source, u8 *_target, u32 n)
{
	const __be16 *source = (const __be16 *)_source;
	u16 *target = (u16 *)_target;
	u32 i;

	for (i = 0; i < n/2; i++)
		target[i] = be16_to_cpu(source[i]);
}