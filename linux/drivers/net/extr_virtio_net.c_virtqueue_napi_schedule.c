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
struct virtqueue {int dummy; } ;
struct napi_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __napi_schedule (struct napi_struct*) ; 
 scalar_t__ napi_schedule_prep (struct napi_struct*) ; 
 int /*<<< orphan*/  virtqueue_disable_cb (struct virtqueue*) ; 

__attribute__((used)) static void virtqueue_napi_schedule(struct napi_struct *napi,
				    struct virtqueue *vq)
{
	if (napi_schedule_prep(napi)) {
		virtqueue_disable_cb(vq);
		__napi_schedule(napi);
	}
}