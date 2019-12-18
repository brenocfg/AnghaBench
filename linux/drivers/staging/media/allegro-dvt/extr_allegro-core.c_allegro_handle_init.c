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
struct mcu_msg_init_response {int dummy; } ;
struct allegro_dev {int /*<<< orphan*/  init_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int allegro_handle_init(struct allegro_dev *dev,
			       struct mcu_msg_init_response *msg)
{
	complete(&dev->init_complete);

	return 0;
}