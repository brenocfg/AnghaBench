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
struct occ {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct occ* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  occ_shutdown (struct occ*) ; 

__attribute__((used)) static int p8_i2c_occ_remove(struct i2c_client *client)
{
	struct occ *occ = dev_get_drvdata(&client->dev);

	occ_shutdown(occ);

	return 0;
}