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
struct adxl34x_platform_data {int dummy; } ;
struct adxl34x {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  adxl34x_send_key_events (struct adxl34x*,struct adxl34x_platform_data*,int,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adxl34x_do_tap(struct adxl34x *ac,
		struct adxl34x_platform_data *pdata, int status)
{
	adxl34x_send_key_events(ac, pdata, status, true);
	input_sync(ac->input);
	adxl34x_send_key_events(ac, pdata, status, false);
}