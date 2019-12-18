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
typedef  int u8 ;
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scl_out (struct qib_devdata*,int) ; 
 scalar_t__ sda_in (struct qib_devdata*,int) ; 

__attribute__((used)) static int i2c_ackrcv(struct qib_devdata *dd)
{
	u8 ack_received;

	/* AT ENTRY SCL = LOW */
	/* change direction, ignore data */
	ack_received = sda_in(dd, 1);
	scl_out(dd, 1);
	ack_received = sda_in(dd, 1) == 0;
	scl_out(dd, 0);
	return ack_received;
}