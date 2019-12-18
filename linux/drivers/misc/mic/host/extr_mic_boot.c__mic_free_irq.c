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
struct mic_irq {int dummy; } ;
struct mbus_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbdev_to_mdev (struct mbus_device*) ; 
 int /*<<< orphan*/  mic_free_irq (int /*<<< orphan*/ ,struct mic_irq*,void*) ; 

__attribute__((used)) static void _mic_free_irq(struct mbus_device *mbdev,
			  struct mic_irq *cookie, void *data)
{
	mic_free_irq(mbdev_to_mdev(mbdev), cookie, data);
}