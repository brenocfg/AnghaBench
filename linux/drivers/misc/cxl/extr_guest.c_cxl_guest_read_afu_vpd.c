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
struct cxl_afu {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  guest_collect_vpd (int /*<<< orphan*/ *,struct cxl_afu*,void*,size_t) ; 

ssize_t cxl_guest_read_afu_vpd(struct cxl_afu *afu, void *buf, size_t len)
{
	return guest_collect_vpd(NULL, afu, buf, len);
}