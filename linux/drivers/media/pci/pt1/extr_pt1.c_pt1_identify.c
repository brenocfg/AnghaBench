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
struct pt1 {int dummy; } ;

/* Variables and functions */
 int pt1_read_reg (struct pt1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt1_write_reg (struct pt1*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u64 pt1_identify(struct pt1 *pt1)
{
	int i;
	u64 id;
	id = 0;
	for (i = 0; i < 57; i++) {
		id |= (u64)(pt1_read_reg(pt1, 0) >> 30 & 1) << i;
		pt1_write_reg(pt1, 0, 0x00000008);
	}
	return id;
}