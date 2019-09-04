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
struct em_i2c_device {int base; } ;

/* Variables and functions */
 int readb (int) ; 
 int /*<<< orphan*/  writeb (int,int) ; 

__attribute__((used)) static inline void em_clear_set_bit(struct em_i2c_device *priv, u8 clear, u8 set, u8 reg)
{
	writeb((readb(priv->base + reg) & ~clear) | set, priv->base + reg);
}