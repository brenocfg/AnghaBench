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
struct mddev {int dummy; } ;
struct linear_conf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct linear_conf*) ; 

__attribute__((used)) static void linear_free(struct mddev *mddev, void *priv)
{
	struct linear_conf *conf = priv;

	kfree(conf);
}