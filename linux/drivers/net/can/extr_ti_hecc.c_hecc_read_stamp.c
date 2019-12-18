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
struct ti_hecc_priv {scalar_t__ hecc_ram; } ;

/* Variables and functions */
 scalar_t__ HECC_CANMOTS ; 
 int __raw_readl (scalar_t__) ; 

__attribute__((used)) static inline u32 hecc_read_stamp(struct ti_hecc_priv *priv, u32 mbxno)
{
	return __raw_readl(priv->hecc_ram + HECC_CANMOTS + mbxno * 4);
}