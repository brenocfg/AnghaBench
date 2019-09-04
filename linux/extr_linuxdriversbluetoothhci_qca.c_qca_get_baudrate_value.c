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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  QCA_BAUDRATE_1000000 ; 
 int /*<<< orphan*/  QCA_BAUDRATE_115200 ; 
 int /*<<< orphan*/  QCA_BAUDRATE_19200 ; 
 int /*<<< orphan*/  QCA_BAUDRATE_2000000 ; 
 int /*<<< orphan*/  QCA_BAUDRATE_230400 ; 
 int /*<<< orphan*/  QCA_BAUDRATE_3000000 ; 
 int /*<<< orphan*/  QCA_BAUDRATE_3200000 ; 
 int /*<<< orphan*/  QCA_BAUDRATE_3500000 ; 
 int /*<<< orphan*/  QCA_BAUDRATE_38400 ; 
 int /*<<< orphan*/  QCA_BAUDRATE_460800 ; 
 int /*<<< orphan*/  QCA_BAUDRATE_500000 ; 
 int /*<<< orphan*/  QCA_BAUDRATE_57600 ; 
 int /*<<< orphan*/  QCA_BAUDRATE_921600 ; 
 int /*<<< orphan*/  QCA_BAUDRATE_9600 ; 

__attribute__((used)) static uint8_t qca_get_baudrate_value(int speed)
{
	switch (speed) {
	case 9600:
		return QCA_BAUDRATE_9600;
	case 19200:
		return QCA_BAUDRATE_19200;
	case 38400:
		return QCA_BAUDRATE_38400;
	case 57600:
		return QCA_BAUDRATE_57600;
	case 115200:
		return QCA_BAUDRATE_115200;
	case 230400:
		return QCA_BAUDRATE_230400;
	case 460800:
		return QCA_BAUDRATE_460800;
	case 500000:
		return QCA_BAUDRATE_500000;
	case 921600:
		return QCA_BAUDRATE_921600;
	case 1000000:
		return QCA_BAUDRATE_1000000;
	case 2000000:
		return QCA_BAUDRATE_2000000;
	case 3000000:
		return QCA_BAUDRATE_3000000;
	case 3200000:
		return QCA_BAUDRATE_3200000;
	case 3500000:
		return QCA_BAUDRATE_3500000;
	default:
		return QCA_BAUDRATE_115200;
	}
}