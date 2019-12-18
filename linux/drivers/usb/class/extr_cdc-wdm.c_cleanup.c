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
struct wdm_device {struct wdm_device* ubuf; struct wdm_device* irq; struct wdm_device* orq; struct wdm_device* inbuf; struct wdm_device* sbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_urbs (struct wdm_device*) ; 
 int /*<<< orphan*/  kfree (struct wdm_device*) ; 

__attribute__((used)) static void cleanup(struct wdm_device *desc)
{
	kfree(desc->sbuf);
	kfree(desc->inbuf);
	kfree(desc->orq);
	kfree(desc->irq);
	kfree(desc->ubuf);
	free_urbs(desc);
	kfree(desc);
}