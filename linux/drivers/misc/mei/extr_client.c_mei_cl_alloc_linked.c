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
struct mei_device {int dummy; } ;
struct mei_cl {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mei_cl* ERR_PTR (int) ; 
 int /*<<< orphan*/  kfree (struct mei_cl*) ; 
 struct mei_cl* mei_cl_allocate (struct mei_device*) ; 
 int mei_cl_link (struct mei_cl*) ; 

struct mei_cl *mei_cl_alloc_linked(struct mei_device *dev)
{
	struct mei_cl *cl;
	int ret;

	cl = mei_cl_allocate(dev);
	if (!cl) {
		ret = -ENOMEM;
		goto err;
	}

	ret = mei_cl_link(cl);
	if (ret)
		goto err;

	return cl;
err:
	kfree(cl);
	return ERR_PTR(ret);
}