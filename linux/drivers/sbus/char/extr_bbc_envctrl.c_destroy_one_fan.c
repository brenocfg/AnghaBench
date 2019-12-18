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
struct bbc_fan_control {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  bbc_i2c_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bbc_fan_control*) ; 

__attribute__((used)) static void destroy_one_fan(struct bbc_fan_control *fp)
{
	bbc_i2c_detach(fp->client);
	kfree(fp);
}