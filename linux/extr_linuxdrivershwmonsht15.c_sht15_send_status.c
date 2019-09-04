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
struct sht15_data {int /*<<< orphan*/  val_status; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHT15_TSU ; 
 int /*<<< orphan*/  SHT15_WRITE_STATUS ; 
 int gpiod_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sht15_send_byte (struct sht15_data*,int /*<<< orphan*/ ) ; 
 int sht15_send_cmd (struct sht15_data*,int /*<<< orphan*/ ) ; 
 int sht15_wait_for_response (struct sht15_data*) ; 

__attribute__((used)) static int sht15_send_status(struct sht15_data *data, u8 status)
{
	int err;

	err = sht15_send_cmd(data, SHT15_WRITE_STATUS);
	if (err)
		return err;
	err = gpiod_direction_output(data->data, 1);
	if (err)
		return err;
	ndelay(SHT15_TSU);
	sht15_send_byte(data, status);
	err = sht15_wait_for_response(data);
	if (err)
		return err;

	data->val_status = status;
	return 0;
}