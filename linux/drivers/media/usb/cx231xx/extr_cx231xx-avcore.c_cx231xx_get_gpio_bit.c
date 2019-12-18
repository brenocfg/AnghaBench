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
typedef  int /*<<< orphan*/  u32 ;
struct cx231xx {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int cx231xx_send_gpio_cmd (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cx231xx_get_gpio_bit(struct cx231xx *dev, u32 gpio_bit, u32 *gpio_val)
{
	__le32 tmp;
	int status = 0;

	status = cx231xx_send_gpio_cmd(dev, gpio_bit, (u8 *)&tmp, 4, 0, 1);
	*gpio_val = le32_to_cpu(tmp);

	return status;
}