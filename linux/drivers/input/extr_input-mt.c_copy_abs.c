#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct input_dev {int /*<<< orphan*/ * absbit; TYPE_1__* absinfo; } ;
struct TYPE_2__ {scalar_t__ fuzz; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_MASK (unsigned int) ; 
 size_t BIT_WORD (unsigned int) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void copy_abs(struct input_dev *dev, unsigned int dst, unsigned int src)
{
	if (dev->absinfo && test_bit(src, dev->absbit)) {
		dev->absinfo[dst] = dev->absinfo[src];
		dev->absinfo[dst].fuzz = 0;
		dev->absbit[BIT_WORD(dst)] |= BIT_MASK(dst);
	}
}