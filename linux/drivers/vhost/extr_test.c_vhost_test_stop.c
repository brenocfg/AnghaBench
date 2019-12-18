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
struct vhost_test {scalar_t__ vqs; } ;

/* Variables and functions */
 scalar_t__ VHOST_TEST_VQ ; 
 void* vhost_test_stop_vq (struct vhost_test*,scalar_t__) ; 

__attribute__((used)) static void vhost_test_stop(struct vhost_test *n, void **privatep)
{
	*privatep = vhost_test_stop_vq(n, n->vqs + VHOST_TEST_VQ);
}