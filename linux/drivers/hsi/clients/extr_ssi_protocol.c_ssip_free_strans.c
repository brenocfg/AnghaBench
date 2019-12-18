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
struct hsi_msg {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ssip_free_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssip_release_cmd (struct hsi_msg*) ; 

__attribute__((used)) static void ssip_free_strans(struct hsi_msg *msg)
{
	ssip_free_data(msg->context);
	ssip_release_cmd(msg);
}