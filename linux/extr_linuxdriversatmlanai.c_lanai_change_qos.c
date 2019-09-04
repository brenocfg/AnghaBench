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
struct atm_vcc {int dummy; } ;
struct atm_qos {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 

__attribute__((used)) static int lanai_change_qos(struct atm_vcc *atmvcc,
	/*const*/ struct atm_qos *qos, int flags)
{
	return -EBUSY;		/* TODO: need to write this */
}