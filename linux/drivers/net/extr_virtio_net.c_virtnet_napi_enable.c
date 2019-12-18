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
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  napi_enable (struct napi_struct*) ; 
 int /*<<< orphan*/  virtqueue_napi_schedule (struct napi_struct*,struct virtqueue*) ; 

__attribute__((used)) static void virtnet_napi_enable(struct virtqueue *vq, struct napi_struct *napi)
{
	napi_enable(napi);

	/* If all buffers were filled by other side before we napi_enabled, we
	 * won't get another interrupt, so process any outstanding packets now.
	 * Call local_bh_enable after to trigger softIRQ processing.
	 */
	local_bh_disable();
	virtqueue_napi_schedule(napi, vq);
	local_bh_enable();
}