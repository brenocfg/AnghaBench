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
struct urdev {int class; } ;

/* Variables and functions */
#define  DEV_CLASS_UR_I 129 
#define  DEV_CLASS_UR_O 128 
 int EOPNOTSUPP ; 
 int verify_uri_device (struct urdev*) ; 

__attribute__((used)) static int verify_device(struct urdev *urd)
{
	switch (urd->class) {
	case DEV_CLASS_UR_O:
		return 0; /* no check needed here */
	case DEV_CLASS_UR_I:
		return verify_uri_device(urd);
	default:
		return -EOPNOTSUPP;
	}
}