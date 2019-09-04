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
struct ubx_data {int /*<<< orphan*/  vcc; } ;
struct gnss_serial {int dummy; } ;

/* Variables and functions */
 struct ubx_data* gnss_serial_get_drvdata (struct gnss_serial*) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ubx_set_standby(struct gnss_serial *gserial)
{
	struct ubx_data *data = gnss_serial_get_drvdata(gserial);
	int ret;

	ret = regulator_disable(data->vcc);
	if (ret)
		return ret;

	return 0;
}