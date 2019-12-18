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
struct ican3_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ican3_msg_disconnect (struct ican3_dev*) ; 
 int /*<<< orphan*/  ican3_reset_module (struct ican3_dev*) ; 

__attribute__((used)) static void ican3_shutdown_module(struct ican3_dev *mod)
{
	ican3_msg_disconnect(mod);
	ican3_reset_module(mod);
}