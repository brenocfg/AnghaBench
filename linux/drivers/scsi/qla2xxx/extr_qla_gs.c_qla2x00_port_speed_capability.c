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
typedef  int uint16_t ;

/* Variables and functions */
#define  BIT_10 135 
#define  BIT_11 134 
#define  BIT_12 133 
#define  BIT_13 132 
#define  BIT_14 131 
#define  BIT_15 130 
#define  BIT_7 129 
#define  BIT_8 128 
 int PORT_SPEED_10GB ; 
 int PORT_SPEED_16GB ; 
 int PORT_SPEED_1GB ; 
 int PORT_SPEED_2GB ; 
 int PORT_SPEED_32GB ; 
 int PORT_SPEED_4GB ; 
 int PORT_SPEED_64GB ; 
 int PORT_SPEED_8GB ; 
 int PORT_SPEED_UNKNOWN ; 

__attribute__((used)) static uint16_t
qla2x00_port_speed_capability(uint16_t speed)
{
	switch (speed) {
	case BIT_15:
		return PORT_SPEED_1GB;
	case BIT_14:
		return PORT_SPEED_2GB;
	case BIT_13:
		return PORT_SPEED_4GB;
	case BIT_12:
		return PORT_SPEED_10GB;
	case BIT_11:
		return PORT_SPEED_8GB;
	case BIT_10:
		return PORT_SPEED_16GB;
	case BIT_8:
		return PORT_SPEED_32GB;
	case BIT_7:
		return PORT_SPEED_64GB;
	default:
		return PORT_SPEED_UNKNOWN;
	}
}