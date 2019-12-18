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
struct allegro_dev {int /*<<< orphan*/  firmware; } ;

/* Variables and functions */
 int /*<<< orphan*/  allegro_free_buffer (struct allegro_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void allegro_free_fw_codec(struct allegro_dev *dev)
{
	allegro_free_buffer(dev, &dev->firmware);
}