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
struct ishtp_cl_device {int /*<<< orphan*/  ishtp_dev; } ;
struct ishtp_cl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ishtp_cl_init (struct ishtp_cl*,int /*<<< orphan*/ ) ; 
 struct ishtp_cl* kmalloc (int,int /*<<< orphan*/ ) ; 

struct ishtp_cl *ishtp_cl_allocate(struct ishtp_cl_device *cl_device)
{
	struct ishtp_cl *cl;

	cl = kmalloc(sizeof(struct ishtp_cl), GFP_KERNEL);
	if (!cl)
		return NULL;

	ishtp_cl_init(cl, cl_device->ishtp_dev);
	return cl;
}