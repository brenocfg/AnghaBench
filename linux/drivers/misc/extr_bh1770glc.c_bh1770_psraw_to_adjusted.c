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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct bh1770_chip {scalar_t__ prox_const; int prox_coef; } ;

/* Variables and functions */
 int BH1770_COEF_SCALER ; 
 scalar_t__ BH1770_PROX_RANGE ; 

__attribute__((used)) static inline u8 bh1770_psraw_to_adjusted(struct bh1770_chip *chip, u8 psraw)
{
	u16 adjusted;
	adjusted = (u16)(((u32)(psraw + chip->prox_const) * chip->prox_coef) /
		BH1770_COEF_SCALER);
	if (adjusted > BH1770_PROX_RANGE)
		adjusted = BH1770_PROX_RANGE;
	return adjusted;
}