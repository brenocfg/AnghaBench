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
struct xc2028_data {int state; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
#define  XC2028_ACTIVE 132 
#define  XC2028_NODEV 131 
#define  XC2028_NO_FIRMWARE 130 
#define  XC2028_SLEEP 129 
#define  XC2028_WAITING_FIRMWARE 128 

__attribute__((used)) static int check_device_status(struct xc2028_data *priv)
{
	switch (priv->state) {
	case XC2028_NO_FIRMWARE:
	case XC2028_WAITING_FIRMWARE:
		return -EAGAIN;
	case XC2028_ACTIVE:
		return 1;
	case XC2028_SLEEP:
		return 0;
	case XC2028_NODEV:
		return -ENODEV;
	}
	return 0;
}