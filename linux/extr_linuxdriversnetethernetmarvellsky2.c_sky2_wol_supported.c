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
typedef  int u8 ;
struct sky2_hw {int dummy; } ;

/* Variables and functions */
 int WAKE_MAGIC ; 
 int WAKE_PHY ; 
 scalar_t__ sky2_is_copper (struct sky2_hw const*) ; 

__attribute__((used)) static inline u8 sky2_wol_supported(const struct sky2_hw *hw)
{
	return sky2_is_copper(hw) ? (WAKE_PHY | WAKE_MAGIC) : 0;
}