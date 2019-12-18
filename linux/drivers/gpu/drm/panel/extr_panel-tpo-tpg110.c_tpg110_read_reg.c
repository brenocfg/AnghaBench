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
struct tpg110 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tpg110_readwrite_reg (struct tpg110*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 tpg110_read_reg(struct tpg110 *tpg, u8 address)
{
	return tpg110_readwrite_reg(tpg, false, address, 0);
}