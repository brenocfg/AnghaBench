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
typedef  int /*<<< orphan*/  u16 ;
struct sky2_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SK_GMAC_REG (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sky2_read16 (struct sky2_hw const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 gma_read16(const struct sky2_hw *hw, unsigned port, unsigned reg)
{
	return sky2_read16(hw, SK_GMAC_REG(port,reg));
}