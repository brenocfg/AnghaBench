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
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int unicam_s_input(struct file *file, void *priv, unsigned int i)
{
	/*
	 * FIXME: Ideally we would like to be able to query the source
	 * subdevice for information over the input connectors it supports,
	 * and map that through in to a call to video_ops->s_routing.
	 * There is no infrastructure support for defining that within
	 * devicetree at present. Until that is implemented we can't
	 * map a user physical connector number to s_routing input number.
	 */
	if (i > 0)
		return -EINVAL;

	return 0;
}