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
struct tpm_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  ops_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void tpm_put_ops(struct tpm_chip *chip)
{
	up_read(&chip->ops_sem);
	put_device(&chip->dev);
}