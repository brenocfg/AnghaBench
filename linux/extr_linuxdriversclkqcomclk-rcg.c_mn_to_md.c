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
typedef  int u32 ;
struct mn {int m_val_shift; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 mn_to_md(struct mn *mn, u32 m, u32 n, u32 md)
{
	u32 mask, mask_w;

	mask_w = BIT(mn->width) - 1;
	mask = (mask_w << mn->m_val_shift) | mask_w;
	md &= ~mask;

	if (n) {
		m <<= mn->m_val_shift;
		md |= m;
		md |= ~n & mask_w;
	}

	return md;
}