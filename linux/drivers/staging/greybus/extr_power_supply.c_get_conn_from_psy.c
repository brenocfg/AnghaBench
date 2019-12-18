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
struct gb_power_supply {TYPE_1__* supplies; } ;
struct gb_connection {int dummy; } ;
struct TYPE_2__ {struct gb_connection* connection; } ;

/* Variables and functions */

__attribute__((used)) static struct gb_connection *get_conn_from_psy(struct gb_power_supply *gbpsy)
{
	return gbpsy->supplies->connection;
}