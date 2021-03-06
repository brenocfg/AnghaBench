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
struct tifm_device_id {scalar_t__ type; } ;
struct tifm_dev {scalar_t__ type; } ;

/* Variables and functions */

__attribute__((used)) static int tifm_dev_match(struct tifm_dev *sock, struct tifm_device_id *id)
{
	if (sock->type == id->type)
		return 1;
	return 0;
}