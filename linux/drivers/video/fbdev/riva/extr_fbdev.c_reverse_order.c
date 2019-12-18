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
 int /*<<< orphan*/  bitrev8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void reverse_order(u32 *l)
{
	u8 *a = (u8 *)l;
	a[0] = bitrev8(a[0]);
	a[1] = bitrev8(a[1]);
	a[2] = bitrev8(a[2]);
	a[3] = bitrev8(a[3]);
}