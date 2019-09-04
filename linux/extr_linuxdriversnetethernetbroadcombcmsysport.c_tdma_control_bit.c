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
struct bcm_sysport_priv {int /*<<< orphan*/  is_lite; } ;

/* Variables and functions */
 scalar_t__ ACB_ALGO ; 
 scalar_t__ BIT (scalar_t__) ; 

__attribute__((used)) static inline u32 tdma_control_bit(struct bcm_sysport_priv *priv, u32 bit)
{
	if (!priv->is_lite) {
		return BIT(bit);
	} else {
		if (bit >= ACB_ALGO)
			return BIT(bit + 1);
		else
			return BIT(bit);
	}
}