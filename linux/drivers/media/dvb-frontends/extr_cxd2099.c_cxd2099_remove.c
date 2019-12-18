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
struct i2c_client {int dummy; } ;
struct cxd {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 struct cxd* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct cxd*) ; 
 int /*<<< orphan*/  regmap_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxd2099_remove(struct i2c_client *client)
{
	struct cxd *ci = i2c_get_clientdata(client);

	regmap_exit(ci->regmap);
	kfree(ci);

	return 0;
}