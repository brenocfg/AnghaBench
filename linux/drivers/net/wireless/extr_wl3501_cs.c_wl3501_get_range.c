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
struct TYPE_2__ {int length; } ;
union iwreq_data {TYPE_1__ data; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_range {int we_version_source; int throughput; int /*<<< orphan*/  we_version_compiled; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIRELESS_EXT ; 
 int /*<<< orphan*/  memset (struct iw_range*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wl3501_get_range(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	struct iw_range *range = (struct iw_range *)extra;

	/* Set the length (very important for backward compatibility) */
	wrqu->data.length = sizeof(*range);

	/* Set all the info we don't care or don't know about to zero */
	memset(range, 0, sizeof(*range));

	/* Set the Wireless Extension versions */
	range->we_version_compiled	= WIRELESS_EXT;
	range->we_version_source	= 1;
	range->throughput		= 2 * 1000 * 1000;     /* ~2 Mb/s */
	/* FIXME: study the code to fill in more fields... */
	return 0;
}