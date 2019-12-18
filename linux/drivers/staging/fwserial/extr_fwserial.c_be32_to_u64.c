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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

inline u64 be32_to_u64(__be32 hi, __be32 lo)
{
	return ((u64)be32_to_cpu(hi) << 32 | be32_to_cpu(lo));
}