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
struct nvkm_msgqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgqueue_0137c63d (struct nvkm_msgqueue*) ; 

__attribute__((used)) static void
msgqueue_0137c63d_dtor(struct nvkm_msgqueue *queue)
{
	kfree(msgqueue_0137c63d(queue));
}