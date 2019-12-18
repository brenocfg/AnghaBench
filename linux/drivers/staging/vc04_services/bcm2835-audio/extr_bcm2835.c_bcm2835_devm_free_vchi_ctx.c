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
struct device {int dummy; } ;
struct bcm2835_vchi_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_free_vchi_ctx (struct bcm2835_vchi_ctx*) ; 

__attribute__((used)) static void bcm2835_devm_free_vchi_ctx(struct device *dev, void *res)
{
	struct bcm2835_vchi_ctx *vchi_ctx = res;

	bcm2835_free_vchi_ctx(vchi_ctx);
}