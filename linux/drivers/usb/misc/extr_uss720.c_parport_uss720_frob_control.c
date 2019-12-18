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
struct parport_uss720_private {unsigned char* reg; } ;
struct parport {struct parport_uss720_private* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ set_1284_register (struct parport*,int,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char parport_uss720_frob_control(struct parport *pp, unsigned char mask, unsigned char val)
{
	struct parport_uss720_private *priv = pp->private_data;	
	unsigned char d;

	mask &= 0x0f;
	val &= 0x0f;
	d = (priv->reg[1] & (~mask)) ^ val;
	if (set_1284_register(pp, 2, d, GFP_ATOMIC))
		return 0;
	priv->reg[1] = d;
	return d & 0xf;
}