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
typedef  int u16 ;

/* Variables and functions */
 int ENXIO ; 
 int ETP_FW_PAGE_SIZE ; 
 int ETP_FW_SIGNATURE_SIZE ; 

__attribute__((used)) static int elan_get_fwinfo(u16 ic_type, u16 *validpage_count,
			   u16 *signature_address)
{
	switch (ic_type) {
	case 0x00:
	case 0x06:
	case 0x08:
		*validpage_count = 512;
		break;
	case 0x03:
	case 0x07:
	case 0x09:
	case 0x0A:
	case 0x0B:
	case 0x0C:
		*validpage_count = 768;
		break;
	case 0x0D:
		*validpage_count = 896;
		break;
	case 0x0E:
		*validpage_count = 640;
		break;
	case 0x10:
		*validpage_count = 1024;
		break;
	default:
		/* unknown ic type clear value */
		*validpage_count = 0;
		*signature_address = 0;
		return -ENXIO;
	}

	*signature_address =
		(*validpage_count * ETP_FW_PAGE_SIZE) - ETP_FW_SIGNATURE_SIZE;

	return 0;
}