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
struct idt_89hpesx_dev {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_set_clientdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void idt_free_pdev(struct idt_89hpesx_dev *pdev)
{
	/* Clear driver data from device private field */
	i2c_set_clientdata(pdev->client, NULL);
}