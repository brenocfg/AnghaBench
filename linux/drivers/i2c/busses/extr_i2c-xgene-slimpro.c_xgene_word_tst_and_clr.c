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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 xgene_word_tst_and_clr(u16 *addr, u16 mask)
{
	u16 ret, val;

	val = le16_to_cpu(READ_ONCE(*addr));
	ret = val & mask;
	val &= ~mask;
	WRITE_ONCE(*addr, cpu_to_le16(val));

	return ret;
}