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
struct snd_tea575x {struct maxiradio* private_data; } ;
struct maxiradio {int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int TEA575X_DATA ; 
 int TEA575X_MOST ; 
 int data ; 
 int inb (int /*<<< orphan*/ ) ; 
 int mo_st ; 

__attribute__((used)) static u8 maxiradio_tea575x_get_pins(struct snd_tea575x *tea)
{
	struct maxiradio *dev = tea->private_data;
	u8 bits = inb(dev->io);

	return  ((bits & data) ? TEA575X_DATA : 0) |
		((bits & mo_st) ? TEA575X_MOST : 0);
}