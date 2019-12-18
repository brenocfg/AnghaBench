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
struct wbsd_host {int base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  request_region (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wbsd_request_region(struct wbsd_host *host, int base)
{
	if (base & 0x7)
		return -EINVAL;

	if (!request_region(base, 8, DRIVER_NAME))
		return -EIO;

	host->base = base;

	return 0;
}