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
typedef  int /*<<< orphan*/  u8 ;
struct ite_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IT85_C0DR ; 
 int /*<<< orphan*/  it8709_wr (struct ite_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void it8709_put_tx_byte(struct ite_dev *dev, u8 value)
{
	it8709_wr(dev, value, IT85_C0DR);
}