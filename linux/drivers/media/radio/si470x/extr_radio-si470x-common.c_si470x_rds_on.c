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
struct si470x_device {int (* set_register ) (struct si470x_device*,size_t) ;int /*<<< orphan*/ * registers; } ;

/* Variables and functions */
 size_t SYSCONFIG1 ; 
 int /*<<< orphan*/  SYSCONFIG1_RDS ; 
 int stub1 (struct si470x_device*,size_t) ; 

__attribute__((used)) static int si470x_rds_on(struct si470x_device *radio)
{
	int retval;

	/* sysconfig 1 */
	radio->registers[SYSCONFIG1] |= SYSCONFIG1_RDS;
	retval = radio->set_register(radio, SYSCONFIG1);
	if (retval < 0)
		radio->registers[SYSCONFIG1] &= ~SYSCONFIG1_RDS;

	return retval;
}