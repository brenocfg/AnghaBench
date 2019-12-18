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
struct snd_tea575x {struct fmr2* private_data; } ;
struct fmr2 {int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int STR_DATA ; 
 int STR_MOST ; 
 int TEA575X_DATA ; 
 int TEA575X_MOST ; 
 int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 fmr2_tea575x_get_pins(struct snd_tea575x *tea)
{
	struct fmr2 *fmr2 = tea->private_data;
	u8 bits = inb(fmr2->io);

	return  ((bits & STR_DATA) ? TEA575X_DATA : 0) |
		((bits & STR_MOST) ? TEA575X_MOST : 0);
}