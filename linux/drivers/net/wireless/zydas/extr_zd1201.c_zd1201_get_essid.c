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
struct zd1201 {int /*<<< orphan*/  essidlen; int /*<<< orphan*/  essid; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int flags; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct zd1201* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int zd1201_get_essid(struct net_device *dev,
    struct iw_request_info *info, struct iw_point *data, char *essid)
{
	struct zd1201 *zd = netdev_priv(dev);

	memcpy(essid, zd->essid, zd->essidlen);
	data->flags = 1;
	data->length = zd->essidlen;

	return 0;
}