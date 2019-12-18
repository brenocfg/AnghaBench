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
struct nfp_resource {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfp_resource*) ; 
 int /*<<< orphan*/  nfp_cpp_mutex_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_cpp_mutex_unlock (int /*<<< orphan*/ ) ; 

void nfp_resource_release(struct nfp_resource *res)
{
	nfp_cpp_mutex_unlock(res->mutex);
	nfp_cpp_mutex_free(res->mutex);
	kfree(res);
}