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
struct ap_message {int /*<<< orphan*/  private; int /*<<< orphan*/  message; } ;

/* Variables and functions */
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ap_release_message(struct ap_message *ap_msg)
{
	kzfree(ap_msg->message);
	kzfree(ap_msg->private);
}