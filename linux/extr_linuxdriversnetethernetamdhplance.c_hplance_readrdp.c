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
struct lance_private {scalar_t__ base; } ;
typedef  unsigned short __u16 ;

/* Variables and functions */
 scalar_t__ HPLANCE_REGOFF ; 
 scalar_t__ HPLANCE_STATUS ; 
 scalar_t__ LANCE_RDP ; 
 int LE_ACK ; 
 int in_8 (scalar_t__) ; 
 unsigned short in_be16 (scalar_t__) ; 

__attribute__((used)) static unsigned short hplance_readrdp(void *priv)
{
	struct lance_private *lp = (struct lance_private *)priv;
	__u16 value;
	do {
		value = in_be16(lp->base + HPLANCE_REGOFF + LANCE_RDP);
	} while ((in_8(lp->base + HPLANCE_STATUS) & LE_ACK) == 0);
	return value;
}