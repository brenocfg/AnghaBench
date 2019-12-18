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
struct gb_connection {TYPE_1__* bundle; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 int gb_connection_enable (struct gb_connection*) ; 
 int gb_spilib_master_init (struct gb_connection*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spilib_ops ; 

__attribute__((used)) static int gb_fw_spi_connection_init(struct gb_connection *connection)
{
	int ret;

	if (!connection)
		return 0;

	ret = gb_connection_enable(connection);
	if (ret)
		return ret;

	ret = gb_spilib_master_init(connection, &connection->bundle->dev,
				    spilib_ops);
	if (ret) {
		gb_connection_disable(connection);
		return ret;
	}

	return 0;
}