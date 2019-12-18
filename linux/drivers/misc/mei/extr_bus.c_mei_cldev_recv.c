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
typedef  int /*<<< orphan*/  u8 ;
struct mei_cl_device {struct mei_cl* cl; } ;
struct mei_cl {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  __mei_cl_recv (struct mei_cl*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ssize_t mei_cldev_recv(struct mei_cl_device *cldev, u8 *buf, size_t length)
{
	struct mei_cl *cl = cldev->cl;

	return __mei_cl_recv(cl, buf, length, 0, 0);
}