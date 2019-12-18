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
typedef  int u32 ;
struct ti_hecc_priv {int dummy; } ;

/* Variables and functions */
 int hecc_read (struct ti_hecc_priv*,int) ; 
 int /*<<< orphan*/  hecc_write (struct ti_hecc_priv*,int,int) ; 

__attribute__((used)) static inline void hecc_set_bit(struct ti_hecc_priv *priv, int reg,
				u32 bit_mask)
{
	hecc_write(priv, reg, hecc_read(priv, reg) | bit_mask);
}