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
struct sht15_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sht15_send_byte (struct sht15_data*,int /*<<< orphan*/ ) ; 
 int sht15_transmission_start (struct sht15_data*) ; 
 int sht15_wait_for_response (struct sht15_data*) ; 

__attribute__((used)) static int sht15_send_cmd(struct sht15_data *data, u8 cmd)
{
	int err;

	err = sht15_transmission_start(data);
	if (err)
		return err;
	sht15_send_byte(data, cmd);
	return sht15_wait_for_response(data);
}