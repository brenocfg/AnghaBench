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

/* Variables and functions */
 unsigned int AC_ERR_ATA_BUS ; 
 unsigned int AC_ERR_DEV ; 
 unsigned int AC_ERR_HOST_BUS ; 
 unsigned int AC_ERR_HSM ; 
 unsigned int AC_ERR_INVALID ; 
 unsigned int AC_ERR_MEDIA ; 
 unsigned int AC_ERR_NCQ ; 
 unsigned int AC_ERR_NODEV_HINT ; 
 unsigned int AC_ERR_SYSTEM ; 
 unsigned int AC_ERR_TIMEOUT ; 

__attribute__((used)) static const char *ata_err_string(unsigned int err_mask)
{
	if (err_mask & AC_ERR_HOST_BUS)
		return "host bus error";
	if (err_mask & AC_ERR_ATA_BUS)
		return "ATA bus error";
	if (err_mask & AC_ERR_TIMEOUT)
		return "timeout";
	if (err_mask & AC_ERR_HSM)
		return "HSM violation";
	if (err_mask & AC_ERR_SYSTEM)
		return "internal error";
	if (err_mask & AC_ERR_MEDIA)
		return "media error";
	if (err_mask & AC_ERR_INVALID)
		return "invalid argument";
	if (err_mask & AC_ERR_DEV)
		return "device error";
	if (err_mask & AC_ERR_NCQ)
		return "NCQ error";
	if (err_mask & AC_ERR_NODEV_HINT)
		return "Polling detection error";
	return "unknown error";
}