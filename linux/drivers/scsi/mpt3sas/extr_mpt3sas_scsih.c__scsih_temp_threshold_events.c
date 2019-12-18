#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct MPT3SAS_ADAPTER {scalar_t__ temp_sensors_count; } ;
struct TYPE_3__ {scalar_t__ SensorNum; int /*<<< orphan*/  CurrentTemperature; int /*<<< orphan*/  Status; } ;
typedef  TYPE_1__ Mpi2EventDataTemperature_t ;

/* Variables and functions */
 int /*<<< orphan*/  ioc_err (struct MPT3SAS_ADAPTER*,char*,char*,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_scsih_temp_threshold_events(struct MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataTemperature_t *event_data)
{
	if (ioc->temp_sensors_count >= event_data->SensorNum) {
		ioc_err(ioc, "Temperature Threshold flags %s%s%s%s exceeded for Sensor: %d !!!\n",
			le16_to_cpu(event_data->Status) & 0x1 ? "0 " : " ",
			le16_to_cpu(event_data->Status) & 0x2 ? "1 " : " ",
			le16_to_cpu(event_data->Status) & 0x4 ? "2 " : " ",
			le16_to_cpu(event_data->Status) & 0x8 ? "3 " : " ",
			event_data->SensorNum);
		ioc_err(ioc, "Current Temp In Celsius: %d\n",
			event_data->CurrentTemperature);
	}
}