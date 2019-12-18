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
struct rhine_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rhine_wait_bit (struct rhine_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rhine_wait_bit_high(struct rhine_private *rp, u8 reg, u8 mask)
{
	rhine_wait_bit(rp, reg, mask, false);
}