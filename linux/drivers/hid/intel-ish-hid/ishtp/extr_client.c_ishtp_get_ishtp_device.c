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
struct ishtp_device {int dummy; } ;
struct ishtp_cl {struct ishtp_device* dev; } ;

/* Variables and functions */

struct ishtp_device *ishtp_get_ishtp_device(struct ishtp_cl *cl)
{
	return cl->dev;
}