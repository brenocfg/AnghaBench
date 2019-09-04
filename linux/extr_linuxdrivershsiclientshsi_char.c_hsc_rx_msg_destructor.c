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
struct hsi_msg {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSI_STATUS_ERROR ; 
 int /*<<< orphan*/  hsc_msg_len_set (struct hsi_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsc_rx_completed (struct hsi_msg*) ; 

__attribute__((used)) static void hsc_rx_msg_destructor(struct hsi_msg *msg)
{
	msg->status = HSI_STATUS_ERROR;
	hsc_msg_len_set(msg, 0);
	hsc_rx_completed(msg);
}