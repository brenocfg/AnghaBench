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
struct alx_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_RXQ0 ; 
 int /*<<< orphan*/  ALX_RXQ0_RSS_HASH_EN ; 
 int /*<<< orphan*/  alx_read_mem32 (struct alx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alx_write_mem32 (struct alx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void alx_disable_rss(struct alx_hw *hw)
{
	u32 ctrl = alx_read_mem32(hw, ALX_RXQ0);

	ctrl &= ~ALX_RXQ0_RSS_HASH_EN;
	alx_write_mem32(hw, ALX_RXQ0, ctrl);
}