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
struct ite_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IT8709_MODE ; 
 int /*<<< orphan*/  IT8709_REG_IDX ; 
 int /*<<< orphan*/  IT8709_REG_VAL ; 
 int IT8709_WRITE ; 
 int /*<<< orphan*/  it8709_wait (struct ite_dev*) ; 
 int /*<<< orphan*/  it8709_wm (struct ite_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void it8709_wr(struct ite_dev *dev, u8 val, int index)
{
	/* we wait before writing, and not afterwards, since this allows us to
	 * pipeline the host CPU with the microcontroller */
	it8709_wait(dev);
	it8709_wm(dev, val, IT8709_REG_VAL);
	it8709_wm(dev, index, IT8709_REG_IDX);
	it8709_wm(dev, IT8709_WRITE, IT8709_MODE);
}