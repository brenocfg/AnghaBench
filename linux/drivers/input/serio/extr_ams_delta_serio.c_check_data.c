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
struct serio {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SERIO_FRAME ; 
 int SERIO_PARITY ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,...) ; 

__attribute__((used)) static int check_data(struct serio *serio, int data)
{
	int i, parity = 0;

	/* check valid stop bit */
	if (!(data & 0x400)) {
		dev_warn(&serio->dev, "invalid stop bit, data=0x%X\n", data);
		return SERIO_FRAME;
	}
	/* calculate the parity */
	for (i = 1; i < 10; i++) {
		if (data & (1 << i))
			parity++;
	}
	/* it should be odd */
	if (!(parity & 0x01)) {
		dev_warn(&serio->dev,
			 "parity check failed, data=0x%X parity=0x%X\n", data,
			 parity);
		return SERIO_PARITY;
	}
	return 0;
}