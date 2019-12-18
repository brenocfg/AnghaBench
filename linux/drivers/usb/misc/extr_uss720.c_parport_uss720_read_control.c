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
struct parport_uss720_private {int* reg; } ;
struct parport {struct parport_uss720_private* private_data; } ;

/* Variables and functions */

__attribute__((used)) static unsigned char parport_uss720_read_control(struct parport *pp)
{
	struct parport_uss720_private *priv = pp->private_data;	
	return priv->reg[1] & 0xf; /* Use soft copy */
}