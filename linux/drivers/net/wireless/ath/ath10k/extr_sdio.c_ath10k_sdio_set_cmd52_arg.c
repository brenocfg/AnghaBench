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
typedef  unsigned char u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int FIELD_PREP (int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  GENMASK (int,int) ; 

__attribute__((used)) static inline void ath10k_sdio_set_cmd52_arg(u32 *arg, u8 write, u8 raw,
					     unsigned int address,
					     unsigned char val)
{
	*arg = FIELD_PREP(BIT(31), write) |
	       FIELD_PREP(BIT(27), raw) |
	       FIELD_PREP(BIT(26), 1) |
	       FIELD_PREP(GENMASK(25, 9), address) |
	       FIELD_PREP(BIT(8), 1) |
	       FIELD_PREP(GENMASK(7, 0), val);
}