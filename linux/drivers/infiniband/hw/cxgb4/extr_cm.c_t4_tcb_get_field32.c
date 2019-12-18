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
typedef  int u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int be64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 t4_tcb_get_field32(__be64 *tcb, u16 word, u32 mask, u32 shift)
{
	u32 v;
	u64 t = be64_to_cpu(tcb[(31 - word) / 2]);

	if (word & 0x1)
		shift += 32;
	v = (t >> shift) & mask;
	return v;
}