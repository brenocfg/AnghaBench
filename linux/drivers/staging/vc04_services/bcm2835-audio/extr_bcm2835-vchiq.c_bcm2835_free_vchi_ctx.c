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
struct bcm2835_vchi_ctx {int /*<<< orphan*/ * vchi_instance; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchi_disconnect (int /*<<< orphan*/ *) ; 

void bcm2835_free_vchi_ctx(struct bcm2835_vchi_ctx *vchi_ctx)
{
	/* Close the VCHI connection - it will also free vchi_instance */
	WARN_ON(vchi_disconnect(vchi_ctx->vchi_instance));

	vchi_ctx->vchi_instance = NULL;
}