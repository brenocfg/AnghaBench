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
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 scalar_t__ max (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __le16 to0based(u32 a)
{
	return cpu_to_le16(max(1U, min(1U << 16, a)) - 1);
}