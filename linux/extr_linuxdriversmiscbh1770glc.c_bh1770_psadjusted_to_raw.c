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
typedef  int u32 ;
typedef  int u16 ;
struct bh1770_chip {int prox_coef; int prox_const; } ;

/* Variables and functions */
 int BH1770_COEF_SCALER ; 

__attribute__((used)) static inline u8 bh1770_psadjusted_to_raw(struct bh1770_chip *chip, u8 ps)
{
	u16 raw;

	raw = (((u32)ps * BH1770_COEF_SCALER) / chip->prox_coef);
	if (raw > chip->prox_const)
		raw = raw - chip->prox_const;
	else
		raw = 0;
	return raw;
}