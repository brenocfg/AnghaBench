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
struct qeth_routing_info {int type; } ;
struct TYPE_2__ {int /*<<< orphan*/  broadcast_capable; } ;
struct qeth_card {TYPE_1__ info; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  MULTICAST_ROUTER 132 
#define  PRIMARY_CONNECTOR 131 
#define  PRIMARY_ROUTER 130 
 int /*<<< orphan*/  QETH_BROADCAST_WITHOUT_ECHO ; 
#define  SECONDARY_CONNECTOR 129 
#define  SECONDARY_ROUTER 128 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t qeth_l3_dev_route_show(struct qeth_card *card,
			struct qeth_routing_info *route, char *buf)
{
	switch (route->type) {
	case PRIMARY_ROUTER:
		return sprintf(buf, "%s\n", "primary router");
	case SECONDARY_ROUTER:
		return sprintf(buf, "%s\n", "secondary router");
	case MULTICAST_ROUTER:
		if (card->info.broadcast_capable == QETH_BROADCAST_WITHOUT_ECHO)
			return sprintf(buf, "%s\n", "multicast router+");
		else
			return sprintf(buf, "%s\n", "multicast router");
	case PRIMARY_CONNECTOR:
		if (card->info.broadcast_capable == QETH_BROADCAST_WITHOUT_ECHO)
			return sprintf(buf, "%s\n", "primary connector+");
		else
			return sprintf(buf, "%s\n", "primary connector");
	case SECONDARY_CONNECTOR:
		if (card->info.broadcast_capable == QETH_BROADCAST_WITHOUT_ECHO)
			return sprintf(buf, "%s\n", "secondary connector+");
		else
			return sprintf(buf, "%s\n", "secondary connector");
	default:
		return sprintf(buf, "%s\n", "no");
	}
}