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
typedef  int /*<<< orphan*/  umode_t ;

/* Variables and functions */
#define  ISCSI_BOOT_INI_INITIATOR_NAME 128 
 int /*<<< orphan*/  S_IRUGO ; 

__attribute__((used)) static umode_t beiscsi_ini_get_attr_visibility(void *data, int type)
{
	umode_t rc = 0;

	switch (type) {
	case ISCSI_BOOT_INI_INITIATOR_NAME:
		rc = S_IRUGO;
		break;
	}
	return rc;
}