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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_DEVICE_ADDRESS ; 
 int cx231xx_read_i2c_data (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,int) ; 

__attribute__((used)) static int afe_read_byte(struct cx231xx *dev, u16 saddr, u8 *data)
{
	int status;
	u32 temp = 0;

	status = cx231xx_read_i2c_data(dev, AFE_DEVICE_ADDRESS,
					saddr, 2, &temp, 1);
	*data = (u8) temp;
	return status;
}