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
struct platform_device {int dummy; } ;
struct bbc_i2c_client {struct platform_device* op; struct bbc_i2c_bus* bp; } ;
struct bbc_i2c_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct bbc_i2c_client*) ; 
 int /*<<< orphan*/  release_device (struct bbc_i2c_bus*,struct platform_device*) ; 

void bbc_i2c_detach(struct bbc_i2c_client *client)
{
	struct bbc_i2c_bus *bp = client->bp;
	struct platform_device *op = client->op;

	release_device(bp, op);
	kfree(client);
}