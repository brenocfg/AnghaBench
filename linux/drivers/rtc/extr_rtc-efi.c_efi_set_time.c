#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  efi_time_t ;
typedef  scalar_t__ efi_status_t ;
struct TYPE_2__ {scalar_t__ (* set_time ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ EFI_SUCCESS ; 
 int EINVAL ; 
 int /*<<< orphan*/  convert_to_efi_time (struct rtc_time*,int /*<<< orphan*/ *) ; 
 TYPE_1__ efi ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efi_set_time(struct device *dev, struct rtc_time *tm)
{
	efi_status_t status;
	efi_time_t eft;

	convert_to_efi_time(tm, &eft);

	status = efi.set_time(&eft);

	return status == EFI_SUCCESS ? 0 : -EINVAL;
}