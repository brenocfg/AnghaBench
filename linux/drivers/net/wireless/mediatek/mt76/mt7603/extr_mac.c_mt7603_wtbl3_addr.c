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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MT7603_WTBL_SIZE ; 
 int MT_WTBL3_SIZE ; 
 scalar_t__ mt7603_wtbl2_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
mt7603_wtbl3_addr(int idx)
{
	u32 base = mt7603_wtbl2_addr(MT7603_WTBL_SIZE);

	return base + idx * MT_WTBL3_SIZE;
}