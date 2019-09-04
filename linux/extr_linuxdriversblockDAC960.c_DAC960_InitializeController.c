#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ expires; } ;
struct TYPE_11__ {int ControllerInitialized; TYPE_2__ MonitoringTimer; } ;
typedef  TYPE_1__ DAC960_Controller_T ;

/* Variables and functions */
 scalar_t__ DAC960_CreateAuxiliaryStructures (TYPE_1__*) ; 
 int /*<<< orphan*/  DAC960_MonitoringTimerFunction ; 
 scalar_t__ DAC960_MonitoringTimerInterval ; 
 scalar_t__ DAC960_ReadControllerConfiguration (TYPE_1__*) ; 
 scalar_t__ DAC960_ReadDeviceConfiguration (TYPE_1__*) ; 
 scalar_t__ DAC960_RegisterBlockDevice (TYPE_1__*) ; 
 scalar_t__ DAC960_ReportControllerConfiguration (TYPE_1__*) ; 
 scalar_t__ DAC960_ReportDeviceConfiguration (TYPE_1__*) ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  timer_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool 
DAC960_InitializeController(DAC960_Controller_T *Controller)
{
  if (DAC960_ReadControllerConfiguration(Controller) &&
      DAC960_ReportControllerConfiguration(Controller) &&
      DAC960_CreateAuxiliaryStructures(Controller) &&
      DAC960_ReadDeviceConfiguration(Controller) &&
      DAC960_ReportDeviceConfiguration(Controller) &&
      DAC960_RegisterBlockDevice(Controller))
    {
      /*
	Initialize the Monitoring Timer.
      */
      timer_setup(&Controller->MonitoringTimer,
                  DAC960_MonitoringTimerFunction, 0);
      Controller->MonitoringTimer.expires =
	jiffies + DAC960_MonitoringTimerInterval;
      add_timer(&Controller->MonitoringTimer);
      Controller->ControllerInitialized = true;
      return true;
    }
  return false;
}