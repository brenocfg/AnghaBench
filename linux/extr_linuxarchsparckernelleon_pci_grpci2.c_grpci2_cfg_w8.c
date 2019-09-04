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
struct grpci2_priv {int dummy; } ;

/* Variables and functions */
 int grpci2_cfg_r32 (struct grpci2_priv*,unsigned int,unsigned int,int,int*) ; 
 int grpci2_cfg_w32 (struct grpci2_priv*,unsigned int,unsigned int,int,int) ; 

__attribute__((used)) static int grpci2_cfg_w8(struct grpci2_priv *priv, unsigned int bus,
				unsigned int devfn, int where, u32 val)
{
	int ret;
	u32 v;

	ret = grpci2_cfg_r32(priv, bus, devfn, where & ~0x3, &v);
	if (ret != 0)
		return ret;
	v = (v & ~(0xff << (8 * (where & 0x3)))) |
	    ((0xff & val) << (8 * (where & 0x3)));
	return grpci2_cfg_w32(priv, bus, devfn, where & ~0x3, v);
}